/*
  This file is part of kdepim.

  Copyright (c) 2004 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2007 Volker Krause <vkrause@kde.org>
  Copyright (c) 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>
  Copyright (C) 2017-2019 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  In addition, as a special exception, the copyright holders give
  permission to link the code of this program with any edition of
  the Qt library by Trolltech AS, Norway (or with modified versions
  of Qt that use the same license as Qt), and distribute linked
  combinations including the two.  You must obey the GNU General
  Public License in all respects for all of the code used other than
  Qt.  If you modify this file, you may extend this exception to
  your version of the file, but you are not obligated to do so.  If
  you do not wish to do so, delete this exception statement from
  your version.
*/
#include "attendeeselector.h"
#include "calendarinterface.h"
#include "delegateselector.h"
#include "memorycalendarmemento.h"
#include "syncitiphandler.h"
#include "reactiontoinvitationdialog.h"

#include <KIdentityManagement/IdentityManager>

#include <MessageViewer/BodyPartURLHandler>
#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessageViewerSettings>
#include <MessageViewer/Viewer>
#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/MessagePart>
using namespace MessageViewer;

#include <KCalCore/ICalFormat>
using namespace KCalCore;

#include <KCalUtils/IncidenceFormatter>

#include <KMime/Message>

#include <KIdentityManagement/Identity>

#include <KEmailAddress>

#include <MailTransportAkonadi/MessageQueueJob>
#include <MailTransport/TransportManager>

#include "text_calendar_debug.h"

#include <KDBusServiceStarter>
#include <KMessageBox>
#include <KRun>
#include <KIO/FileCopyJob>
#include <KIO/StatJob>
#include <KLocalizedString>

#include <QEventLoop>
#include <QDBusServiceWatcher>
#include <QMimeDatabase>
#include <QProcess>
#include <QUrl>
#include <QTemporaryFile>
#include <QIcon>
#include <QFileDialog>
#include <QDesktopServices>
#include <QInputDialog>
#include <QMenu>
#include <QPointer>

using namespace MailTransport;

namespace {
static bool hasMyWritableEventsFolders(const QString &family)
{
    QString myfamily = family;
    if (family.isEmpty()) {
        myfamily = QStringLiteral("calendar");
    }

#if 0 // TODO port to Akonadi
#ifndef KDEPIM_NO_KRESOURCES
    CalendarResourceManager manager(myfamily);
    manager.readConfig();

    CalendarResourceManager::ActiveIterator it;
    for (it = manager.activeBegin(); it != manager.activeEnd(); ++it) {
        if ((*it)->readOnly()) {
            continue;
        }

        const QStringList subResources = (*it)->subresources();
        if (subResources.isEmpty()) {
            return true;
        }

        QStringList::ConstIterator subIt;
        for (subIt = subResources.begin(); subIt != subResources.end(); ++subIt) {
            if (!(*it)->subresourceActive((*subIt))) {
                continue;
            }
            if ((*it)->type() == "imap" || (*it)->type() == "kolab") {
                if ((*it)->subresourceType((*subIt)) == "todo"
                    || (*it)->subresourceType((*subIt)) == "journal"
                    || !(*subIt).contains("/.INBOX.directory/")) {
                    continue;
                }
            }
            return true;
        }
    }
    return false;
#endif
#else
    qCDebug(TEXT_CALENDAR_LOG) << "Disabled code, port to Akonadi";
    return true;
#endif
}

static bool occurredAlready(const Incidence::Ptr &incidence)
{
    Q_ASSERT(incidence);
    const QDateTime now = QDateTime::currentDateTime();
    const QDate today = now.date();

    if (incidence->recurs()) {
        const QDateTime nextDate = incidence->recurrence()->getNextDateTime(now);

        return !nextDate.isValid();
    } else {
        const QDateTime incidenceDate = incidence->dateTime(Incidence::RoleDisplayEnd);
        if (incidenceDate.isValid()) {
            return incidence->allDay() ? (incidenceDate.date() < today) : (incidenceDate < QDateTime::currentDateTime());
        }
    }

    return false;
}

class KMInvitationFormatterHelper : public KCalUtils::InvitationFormatterHelper
{
public:
    KMInvitationFormatterHelper(const MimeTreeParser::MessagePartPtr &bodyPart, const KCalCore::MemoryCalendar::Ptr &calendar)
        : mBodyPart(bodyPart)
        , mCalendar(calendar)
    {
    }

    QString generateLinkURL(const QString &id) override
    {
        return mBodyPart->makeLink(id);
    }

    KCalCore::Calendar::Ptr calendar() const override
    {
        return mCalendar;
    }

private:
    MimeTreeParser::MessagePartPtr mBodyPart;
    KCalCore::MemoryCalendar::Ptr mCalendar;
};

class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *writer, MessageViewer::RenderContext *) const override
    {
        QMimeDatabase db;
        auto mt = db.mimeTypeForName(QString::fromLatin1(msgPart->content()->contentType()->mimeType().toLower()));
        if (!mt.isValid() || mt.name() != QLatin1String("text/calendar")) {
            return false;
        }

        auto nodeHelper = msgPart->nodeHelper();
        if (!nodeHelper) {
            return false;
        }

        /** Formatting is async now because we need to fetch incidences from akonadi.
            Basically this method (format()) will be called twice. The first time
            it creates the memento that fetches incidences and returns.

            When the memento finishes, this is called a second time, and we can proceed.

            BodyPartMementos are documented in MessageViewer/ObjectTreeParser
        */
        MemoryCalendarMemento *memento = dynamic_cast<MemoryCalendarMemento *>(msgPart->memento());

        if (memento) {
            KMime::Message *const message = dynamic_cast<KMime::Message *>(msgPart->content()->topLevel());
            if (!message) {
                qCWarning(TEXT_CALENDAR_LOG) << "The top-level content is not a message. Cannot handle the invitation then.";
                return false;
            }

            if (memento->finished()) {
                KMInvitationFormatterHelper helper(msgPart, memento->calendar());
                QString source;
                // If the bodypart does not have a charset specified, we need to fall back to utf8,
                // not the KMail fallback encoding, so get the contents as binary and decode explicitly.
                if (msgPart->content()->contentType()->parameter(QStringLiteral("charset")).isEmpty()) {
                    const QByteArray &ba = msgPart->content()->decodedContent();
                    source = QString::fromUtf8(ba);
                } else {
                    source = msgPart->text();
                }

                MemoryCalendar::Ptr cl(new MemoryCalendar(QTimeZone::systemTimeZone()));
                const QString html
                    = KCalUtils::IncidenceFormatter::formatICalInvitationNoHtml(
                          source, cl, &helper, message->sender()->asUnicodeString());

                if (html.isEmpty()) {
                    return false;
                }
                writer->write(html);
            }
        } else {
            MemoryCalendarMemento *memento = new MemoryCalendarMemento();
            msgPart->setMemento(memento);
            QObject::connect(memento, &MemoryCalendarMemento::update,
                             nodeHelper, &MimeTreeParser::NodeHelper::update);
        }

        return true;
    }
};

static QString directoryForStatus(Attendee::PartStat status)
{
    QString dir;
    switch (status) {
    case Attendee::Accepted:
        dir = QStringLiteral("accepted");
        break;
    case Attendee::Tentative:
        dir = QStringLiteral("tentative");
        break;
    case Attendee::Declined:
        dir = QStringLiteral("cancel");
        break;
    case Attendee::Delegated:
        dir = QStringLiteral("delegated");
        break;
    case Attendee::NeedsAction:
        dir = QStringLiteral("request");
        break;
    default:
        break;
    }
    return dir;
}

static Incidence::Ptr stringToIncidence(const QString &iCal)
{
    MemoryCalendar::Ptr calendar(new MemoryCalendar(QTimeZone::systemTimeZone()));
    ICalFormat format;
    ScheduleMessage::Ptr message = format.parseScheduleMessage(calendar, iCal);
    if (!message) {
        //TODO: Error message?
        qCWarning(TEXT_CALENDAR_LOG) << "Can't parse this ical string: "  << iCal;
        return Incidence::Ptr();
    }

    return message->event().dynamicCast<Incidence>();
}

class UrlHandler : public MessageViewer::Interface::BodyPartURLHandler
{
public:
    UrlHandler()
    {
        //qCDebug(TEXT_CALENDAR_LOG) << "UrlHandler() (iCalendar)";
    }

    QString name() const override
    {
        return QStringLiteral("calendar handler");
    }

    Attendee findMyself(const Incidence::Ptr &incidence, const QString &receiver) const
    {
        const Attendee::List attendees = incidence->attendees();
        const auto idx = findMyself(attendees, receiver);
        if (idx >= 0) {
            return attendees.at(idx);
        }
        return {};
    }

    int findMyself(const Attendee::List &attendees, const QString &receiver) const
    {
        // Find myself. There will always be all attendees listed, even if
        // only I need to answer it.
        for (int i = 0; i < attendees.size(); ++i) {
            // match only the email part, not the name
            if (KEmailAddress::compareEmail(attendees.at(i).email(), receiver, false)) {
                // We are the current one, and even the receiver, note
                // this and quit searching.
                return i;
                break;
            }
        }
        return -1;
    }

    static bool heuristicalRSVP(const Incidence::Ptr &incidence)
    {
        bool rsvp = true; // better send superfluously than not at all
        const Attendee::List attendees = incidence->attendees();
        Attendee::List::ConstIterator it;
        Attendee::List::ConstIterator end(attendees.constEnd());
        for (it = attendees.constBegin(); it != end; ++it) {
            if (it == attendees.constBegin()) {
                rsvp = (*it).RSVP(); // use what the first one has
            } else {
                if ((*it).RSVP() != rsvp) {
                    rsvp = true; // they differ, default
                    break;
                }
            }
        }
        return rsvp;
    }

    static Attendee::Role heuristicalRole(const Incidence::Ptr &incidence)
    {
        Attendee::Role role = Attendee::OptParticipant;
        const Attendee::List attendees = incidence->attendees();
        Attendee::List::ConstIterator it;
        Attendee::List::ConstIterator end = attendees.constEnd();

        for (it = attendees.constBegin(); it != end; ++it) {
            if (it == attendees.constBegin()) {
                role = (*it).role(); // use what the first one has
            } else {
                if ((*it).role() != role) {
                    role = Attendee::OptParticipant; // they differ, default
                    break;
                }
            }
        }
        return role;
    }

    static Attachment findAttachment(const QString &name, const QString &iCal)
    {
        Incidence::Ptr incidence = stringToIncidence(iCal);

        // get the attachment by name from the incidence
        Attachment::List attachments = incidence->attachments();
        Attachment attachment;
        const Attachment::List::ConstIterator end = attachments.constEnd();
        for (Attachment::List::ConstIterator it = attachments.constBegin(); it != end; ++it) {
            if ((*it).label() == name) {
                attachment = *it;
                break;
            }
        }

        if (attachment.isEmpty()) {
            KMessageBox::error(
                nullptr,
                i18n("No attachment named \"%1\" found in the invitation.", name));
            return Attachment();
        }

        if (attachment.isUri()) {
            bool fileExists = false;
            QUrl attachmentUrl(attachment.uri());
            if (attachmentUrl.isLocalFile()) {
                fileExists = QFile::exists(attachmentUrl.toLocalFile());
            } else {
                auto job = KIO::stat(attachmentUrl, KIO::StatJob::SourceSide, 0);
                fileExists = job->exec();
            }
            if (!fileExists) {
                KMessageBox::information(
                    nullptr,
                    i18n("The invitation attachment \"%1\" is a web link that "
                         "is inaccessible from this computer. Please ask the event "
                         "organizer to resend the invitation with this attachment "
                         "stored inline instead of a link.",
                         attachmentUrl.toDisplayString()));
                return Attachment();
            }
        }
        return attachment;
    }

    static QString findReceiver(KMime::Content *node)
    {
        if (!node || !node->topLevel()) {
            return QString();
        }

        QString receiver;
        KIdentityManagement::IdentityManager *im = KIdentityManagement::IdentityManager::self();

        KMime::Types::Mailbox::List addrs;
        if (auto header = node->topLevel()->header<KMime::Headers::To>()) {
            addrs = header->mailboxes();
        }
        int found = 0;
        QVector< KMime::Types::Mailbox >::const_iterator end = addrs.constEnd();
        for (QVector< KMime::Types::Mailbox >::const_iterator it = addrs.constBegin();
             it != end; ++it) {
            if (im->identityForAddress(QLatin1String((*it).address())) != KIdentityManagement::Identity::null()) {
                // Ok, this could be us
                ++found;
                receiver = QLatin1String((*it).address());
            }
        }

        KMime::Types::Mailbox::List ccaddrs;
        if (auto header = node->topLevel()->header<KMime::Headers::Cc>()) {
            ccaddrs = header->mailboxes();
        }
        end = ccaddrs.constEnd();
        for (QVector<KMime::Types::Mailbox >::const_iterator it = ccaddrs.constBegin();
             it != end; ++it) {
            if (im->identityForAddress(QLatin1String((*it).address())) != KIdentityManagement::Identity::null()) {
                // Ok, this could be us
                ++found;
                receiver = QLatin1String((*it).address());
            }
        }
        if (found != 1) {
            QStringList possibleAddrs;
            bool ok;
            QString selectMessage;
            if (found == 0) {
                selectMessage
                    = i18n("<qt>None of your identities match the receiver of this message,<br/>"
                           "please choose which of the following addresses is yours,<br/> if any, "
                           "or select one of your identities to use in the reply:</qt>");
                possibleAddrs += im->allEmails();
            } else {
                selectMessage
                    = i18n("<qt>Several of your identities match the receiver of this message,<br/>"
                           "please choose which of the following addresses is yours:</qt>");
                for (const KMime::Types::Mailbox &mbx : qAsConst(addrs)) {
                    possibleAddrs.append(QLatin1String(mbx.address()));
                }
                for (const KMime::Types::Mailbox &mbx : qAsConst(ccaddrs)) {
                    possibleAddrs.append(QLatin1String(mbx.address()));
                }
            }

            // select default identity by default
            const QString defaultAddr = im->defaultIdentity().primaryEmailAddress();
            const int defaultIndex = qMax(0, possibleAddrs.indexOf(defaultAddr));

            receiver = QInputDialog::getItem(nullptr,
                                             i18n("Select Address"), selectMessage, possibleAddrs, defaultIndex, false, &ok);

            if (!ok) {
                receiver.clear();
            }
        }
        return receiver;
    }

    Attendee setStatusOnMyself(const Incidence::Ptr &incidence, const Attendee &myself, Attendee::PartStat status, const QString &receiver) const
    {
        QString name;
        QString email;
        KEmailAddress::extractEmailAddressAndName(receiver, email, name);
        if (name.isEmpty() && !myself.isNull()) {
            name = myself.name();
        }
        if (email.isEmpty() && !myself.isNull()) {
            email = myself.email();
        }
        Q_ASSERT(!email.isEmpty());   // delivery must be possible

        Attendee newMyself(name, email, true,  // RSVP, otherwise we would not be here
                         status,
                         !myself.isNull() ? myself.role() : heuristicalRole(incidence),
                         myself.uid());
        if (!myself.isNull()) {
            newMyself.setDelegate(myself.delegate());
            newMyself.setDelegator(myself.delegator());
        }

        // Make sure only ourselves is in the event
        incidence->clearAttendees();
        if (!newMyself.isNull()) {
            incidence->addAttendee(newMyself);
        }
        return newMyself;
    }

    enum MailType {
        Answer,
        Delegation,
        Forward,
        DeclineCounter
    };

    bool mailICal(const QString &receiver, const QString &to, const QString &iCal, const QString &subject, const QString &status, bool delMessage, Viewer *viewerInstance) const
    {
        qCDebug(TEXT_CALENDAR_LOG) << "Mailing message:" << iCal;

        KMime::Message::Ptr msg(new KMime::Message);
        if (MessageViewer::MessageViewerSettings::self()->exchangeCompatibleInvitations()) {
            msg->subject()->fromUnicodeString(status, "utf-8");
            QString tsubject = subject;
            tsubject.remove(i18n("Answer: "));
            if (status == QLatin1String("cancel")) {
                msg->subject()->fromUnicodeString(
                    i18nc("Not able to attend.", "Declined: %1", tsubject), "utf-8");
            } else if (status == QLatin1String("tentative")) {
                msg->subject()->fromUnicodeString(
                    i18nc("Unsure if it is possible to attend.", "Tentative: %1", tsubject), "utf-8");
            } else if (status == QLatin1String("accepted")) {
                msg->subject()->fromUnicodeString(
                    i18nc("Accepted the invitation.", "Accepted: %1", tsubject), "utf-8");
            } else {
                msg->subject()->fromUnicodeString(subject, "utf-8");
            }
        } else {
            msg->subject()->fromUnicodeString(subject, "utf-8");
        }
        msg->to()->fromUnicodeString(to, "utf-8");
        msg->from()->fromUnicodeString(receiver, "utf-8");
        msg->date()->setDateTime(QDateTime::currentDateTime());

        if (MessageViewer::MessageViewerSettings::self()->legacyBodyInvites()) {
            msg->contentType()->setMimeType("text/calendar");
            msg->contentType()->setCharset("utf-8");
            msg->contentType()->setName(QStringLiteral("cal.ics"), "utf-8");
            msg->contentType()->setParameter(QStringLiteral("method"), QStringLiteral("reply"));

            KMime::Headers::ContentDisposition *disposition = new KMime::Headers::ContentDisposition;
            disposition->setDisposition(KMime::Headers::CDinline);
            msg->setHeader(disposition);
            msg->contentTransferEncoding()->setEncoding(KMime::Headers::CEquPr);
            const QString answer = i18n("Invitation answer attached.");
            msg->setBody(answer.toUtf8());
        } else {
            // We need to set following 4 lines by hand else KMime::Content::addContent
            // will create a new Content instance for us to attach the main message
            // what we don't need cause we already have the main message instance where
            // 2 additional messages are attached.
            KMime::Headers::ContentType *ct = msg->contentType();
            ct->setMimeType("multipart/mixed");
            ct->setBoundary(KMime::multiPartBoundary());
            ct->setCategory(KMime::Headers::CCcontainer);

            // Set the first multipart, the body message.
            KMime::Content *bodyMessage = new KMime::Content;
            KMime::Headers::ContentDisposition *bodyDisposition = new KMime::Headers::ContentDisposition;
            bodyDisposition->setDisposition(KMime::Headers::CDinline);
            bodyMessage->contentType()->setMimeType("text/plain");
            bodyMessage->contentType()->setCharset("utf-8");
            bodyMessage->contentTransferEncoding()->setEncoding(KMime::Headers::CEquPr);
            const QString answer = i18n("Invitation answer attached.");
            bodyMessage->setBody(answer.toUtf8());
            bodyMessage->setHeader(bodyDisposition);
            msg->addContent(bodyMessage);

            // Set the second multipart, the attachment.
            KMime::Content *attachMessage = new KMime::Content;
            KMime::Headers::ContentDisposition *attachDisposition = new KMime::Headers::ContentDisposition;
            attachDisposition->setDisposition(KMime::Headers::CDattachment);
            attachMessage->contentType()->setMimeType("text/calendar");
            attachMessage->contentType()->setCharset("utf-8");
            attachMessage->contentType()->setName(QStringLiteral("cal.ics"), "utf-8");
            attachMessage->contentType()->setParameter(QStringLiteral("method"),
                                                       QStringLiteral("reply"));
            attachMessage->setHeader(attachDisposition);
            attachMessage->contentTransferEncoding()->setEncoding(KMime::Headers::CEquPr);
            attachMessage->setBody(KMime::CRLFtoLF(iCal.toUtf8()));
            msg->addContent(attachMessage);
        }

        // Try and match the receiver with an identity.
        // Setting the identity here is important, as that is used to select the correct
        // transport later
        KIdentityManagement::IdentityManager *im = KIdentityManagement::IdentityManager::self();
        const KIdentityManagement::Identity identity
            = im->identityForAddress(
                  findReceiver(viewerInstance->message().data()));

        const bool nullIdentity = (identity == KIdentityManagement::Identity::null());

        if (!nullIdentity) {
            KMime::Headers::Generic *x_header = new KMime::Headers::Generic("X-KMail-Identity");
            x_header->from7BitString(QByteArray::number(identity.uoid()));
            msg->setHeader(x_header);
        }

        const bool identityHasTransport = !identity.transport().isEmpty();
        int transportId = -1;
        if (!nullIdentity && identityHasTransport) {
            transportId = identity.transport().toInt();
        } else {
            transportId = TransportManager::self()->defaultTransportId();
        }
        if (transportId == -1) {
            if (!TransportManager::self()->showTransportCreationDialog(nullptr, TransportManager::IfNoTransportExists)) {
                return false;
            }
            transportId = TransportManager::self()->defaultTransportId();
        }
        auto header = new KMime::Headers::Generic("X-KMail-Transport");
        header->fromUnicodeString(QString::number(transportId), "utf-8");
        msg->setHeader(header);

        // Outlook will only understand the reply if the From: header is the
        // same as the To: header of the invitation message.
        if (!MessageViewer::MessageViewerSettings::self()->legacyMangleFromToHeaders()) {
            if (identity != KIdentityManagement::Identity::null()) {
                msg->from()->fromUnicodeString(identity.fullEmailAddr(), "utf-8");
            }
            // Remove BCC from identity on ical invitations (kolab/issue474)
            msg->removeHeader<KMime::Headers::Bcc>();
        }

        msg->assemble();
        MailTransport::Transport *transport = MailTransport::TransportManager::self()->transportById(transportId);

        MailTransport::MessageQueueJob *job = new MailTransport::MessageQueueJob;

        job->addressAttribute().setTo(QStringList() << KEmailAddress::extractEmailAddress(
                                          KEmailAddress::normalizeAddressesAndEncodeIdn(to)));
        job->transportAttribute().setTransportId(transport->id());

        if (transport->specifySenderOverwriteAddress()) {
            job->addressAttribute().setFrom(
                KEmailAddress::extractEmailAddress(
                    KEmailAddress::normalizeAddressesAndEncodeIdn(transport->senderOverwriteAddress())));
        } else {
            job->addressAttribute().setFrom(
                KEmailAddress::extractEmailAddress(
                    KEmailAddress::normalizeAddressesAndEncodeIdn(msg->from()->asUnicodeString())));
        }

        job->setMessage(msg);

        if (!job->exec()) {
            qCWarning(TEXT_CALENDAR_LOG) << "Error queuing message in outbox:" << job->errorText();
            return false;
        }
        // We are not notified when mail was sent, so assume it was sent when queued.
        if (delMessage
            && MessageViewer::MessageViewerSettings::self()->deleteInvitationEmailsAfterSendingReply()) {
            viewerInstance->deleteMessage();
        }
        return true;
    }

    bool mail(Viewer *viewerInstance, const Incidence::Ptr &incidence, const QString &status, iTIPMethod method = iTIPReply, const QString &receiver = QString(), const QString &to = QString(), MailType type = Answer) const
    {
        //status is accepted/tentative/declined
        ICalFormat format;
        format.setTimeZone(QTimeZone::systemTimeZone());
        QString msg = format.createScheduleMessage(incidence, method);
        QString summary = incidence->summary();
        if (summary.isEmpty()) {
            summary = i18n("Incidence with no summary");
        }
        QString subject;
        switch (type) {
        case Answer:
            subject = i18n("Answer: %1", summary);
            break;
        case Delegation:
            subject = i18n("Delegated: %1", summary);
            break;
        case Forward:
            subject = i18n("Forwarded: %1", summary);
            break;
        case DeclineCounter:
            subject = i18n("Declined Counter Proposal: %1", summary);
            break;
        }

        // Set the organizer to the sender, if the ORGANIZER hasn't been set.
        if (incidence->organizer().isEmpty()) {
            QString tname, temail;
            KMime::Message::Ptr message = viewerInstance->message();
            KEmailAddress::extractEmailAddressAndName(message->sender()->asUnicodeString(),
                                                      temail, tname);
            incidence->setOrganizer(Person(tname, temail));
        }

        QString recv = to;
        if (recv.isEmpty()) {
            recv = incidence->organizer().fullName();
        }
        return mailICal(receiver, recv, msg, subject, status, type != Forward, viewerInstance);
    }

    bool saveFile(const QString &receiver, const QString &iCal, const QString &type, MimeTreeParser::Interface::BodyPart *bodyPart) const
    {
        MemoryCalendarMemento *memento = dynamic_cast<MemoryCalendarMemento *>(bodyPart->memento());
        // This will block. There's no way to make it async without refactoring the memento mechanism

        SyncItipHandler *itipHandler = new SyncItipHandler(receiver, iCal, type, memento->calendar());

        // If result is ResultCancelled, then we don't show the message box and return false so kmail
        // doesn't delete the e-mail.
        qCDebug(TEXT_CALENDAR_LOG) << "ITIPHandler result was " << itipHandler->result();
        const Akonadi::ITIPHandler::Result res = itipHandler->result();
        if (res == Akonadi::ITIPHandler::ResultError) {
            const QString errorMessage = itipHandler->errorMessage();
            if (!errorMessage.isEmpty()) {
                qCCritical(TEXT_CALENDAR_LOG) << "Error while processing invitation: " << errorMessage;
                KMessageBox::error(nullptr, errorMessage);
            }
            return false;
        }

        return res;
    }

    bool cancelPastInvites(const Incidence::Ptr incidence, const QString &path) const
    {
        QString warnStr;
        QDateTime now = QDateTime::currentDateTime();
        QDate today = now.date();
        Incidence::IncidenceType type = Incidence::TypeUnknown;
        const bool occurred = occurredAlready(incidence);
        if (incidence->type() == Incidence::TypeEvent) {
            type = Incidence::TypeEvent;
            Event::Ptr event = incidence.staticCast<Event>();
            if (!event->allDay()) {
                if (occurred) {
                    warnStr = i18n("\"%1\" occurred already.", event->summary());
                } else if (event->dtStart() <= now && now <= event->dtEnd()) {
                    warnStr = i18n("\"%1\" is currently in-progress.", event->summary());
                }
            } else {
                if (occurred) {
                    warnStr = i18n("\"%1\" occurred already.", event->summary());
                } else if (event->dtStart().date() <= today && today <= event->dtEnd().date()) {
                    warnStr = i18n("\"%1\", happening all day today, is currently in-progress.",
                                   event->summary());
                }
            }
        } else if (incidence->type() == Incidence::TypeTodo) {
            type = Incidence::TypeTodo;
            Todo::Ptr todo = incidence.staticCast<Todo>();
            if (!todo->allDay()) {
                if (todo->hasDueDate()) {
                    if (todo->dtDue() < now) {
                        warnStr = i18n("\"%1\" is past due.", todo->summary());
                    } else if (todo->hasStartDate() && todo->dtStart() <= now && now <= todo->dtDue()) {
                        warnStr = i18n("\"%1\" is currently in-progress.", todo->summary());
                    }
                } else if (todo->hasStartDate()) {
                    if (todo->dtStart() < now) {
                        warnStr = i18n("\"%1\" has already started.", todo->summary());
                    }
                }
            } else {
                if (todo->hasDueDate()) {
                    if (todo->dtDue().date() < today) {
                        warnStr = i18n("\"%1\" is past due.", todo->summary());
                    } else if (todo->hasStartDate()
                               && todo->dtStart().date() <= today && today <= todo->dtDue().date()) {
                        warnStr = i18n("\"%1\", happening all-day today, is currently in-progress.",
                                       todo->summary());
                    }
                } else if (todo->hasStartDate()) {
                    if (todo->dtStart().date() < today) {
                        warnStr = i18n("\"%1\", happening all day, has already started.", todo->summary());
                    }
                }
            }
        }

        if (!warnStr.isEmpty()) {
            QString queryStr;
            if (path == QLatin1String("accept")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to accept the task?");
                } else {
                    queryStr = i18n("Do you still want to accept the invitation?");
                }
            } else if (path == QLatin1String("accept_conditionally")) {
                if (type == Incidence::TypeTodo) {
                    queryStr
                        = i18n("Do you still want to send conditional acceptance of the invitation?");
                } else {
                    queryStr = i18n("Do you still want to send conditional acceptance of the task?");
                }
            } else if (path == QLatin1String("accept_counter")) {
                queryStr = i18n("Do you still want to accept the counter proposal?");
            } else if (path == QLatin1String("counter")) {
                queryStr = i18n("Do you still want to send a counter proposal?");
            } else if (path == QLatin1String("decline")) {
                queryStr = i18n("Do you still want to send a decline response?");
            } else if (path == QLatin1String("decline_counter")) {
                queryStr = i18n("Do you still want to decline the counter proposal?");
            } else if (path == QLatin1String("reply")) {
                queryStr = i18n("Do you still want to record this response in your calendar?");
            } else if (path == QLatin1String("delegate")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to delegate this task?");
                } else {
                    queryStr = i18n("Do you still want to delegate this invitation?");
                }
            } else if (path == QLatin1String("forward")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to forward this task?");
                } else {
                    queryStr = i18n("Do you still want to forward this invitation?");
                }
            } else if (path == QLatin1String("cancel")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to cancel this task?");
                } else {
                    queryStr = i18n("Do you still want to cancel this invitation?");
                }
            } else if (path == QLatin1String("check_calendar")) {
                queryStr = i18n("Do you still want to check your calendar?");
            } else if (path == QLatin1String("record")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to record this task in your calendar?");
                } else {
                    queryStr = i18n("Do you still want to record this invitation in your calendar?");
                }
            } else if (path == QLatin1String("cancel")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you really want to cancel this task?");
                } else {
                    queryStr = i18n("Do you really want to cancel this invitation?");
                }
            } else if (path.startsWith(QLatin1String("ATTACH:"))) {
                return false;
            } else {
                queryStr = i18n("%1?", path);
            }

            if (KMessageBox::warningYesNo(
                    nullptr,
                    i18n("%1\n%2", warnStr, queryStr)) == KMessageBox::No) {
                return true;
            }
        }
        return false;
    }

    bool handleInvitation(const QString &iCal, Attendee::PartStat status, MimeTreeParser::Interface::BodyPart *part, Viewer *viewerInstance) const
    {
        bool ok = true;
        const QString receiver = findReceiver(part->content());
        qCDebug(TEXT_CALENDAR_LOG) << receiver;

        if (receiver.isEmpty()) {
            // Must be some error. Still return true though, since we did handle it
            return true;
        }

        Incidence::Ptr incidence = stringToIncidence(iCal);
        qCDebug(TEXT_CALENDAR_LOG) << "Handling invitation: uid is : " << incidence->uid()
                                   << "; schedulingId is:" << incidence->schedulingID()
                                   << "; Attendee::PartStat = " << status;

        // get comment for tentative acceptance
        if (askForComment(status)) {
            QPointer<ReactionToInvitationDialog> dlg = new ReactionToInvitationDialog(nullptr);
            dlg->setWindowTitle(i18n("Reaction to Invitation"));
            QString comment;
            if (dlg->exec()) {
                comment = dlg->comment();
                delete dlg;
            } else {
                delete dlg;
                return true;
            }

            if (comment.trimmed().isEmpty()) {
                KMessageBox::error(
                    nullptr,
                    i18n("You forgot to add proposal. Please add it. Thanks"));
                return true;
            } else {
                incidence->addComment(comment);
            }
        }

        // First, save it for KOrganizer to handle
        const QString dir = directoryForStatus(status);
        if (dir.isEmpty()) {
            qCWarning(TEXT_CALENDAR_LOG) << "Impossible to understand status: " << status;
            return true; // unknown status
        }
        if (status != Attendee::Delegated) {
            // we do that below for delegated incidences
            if (!saveFile(receiver, iCal, dir, part)) {
                return false;
            }
        }

        QString delegateString;
        bool delegatorRSVP = false;
        if (status == Attendee::Delegated) {
            DelegateSelector dlg;
            if (dlg.exec() == QDialog::Rejected) {
                return true;
            }
            delegateString = dlg.delegate();
            delegatorRSVP = dlg.rsvp();
            if (delegateString.isEmpty()) {
                return true;
            }
            if (KEmailAddress::compareEmail(delegateString, incidence->organizer().email(), false)) {
                KMessageBox::sorry(nullptr, i18n("Delegation to organizer is not possible."));
                return true;
            }
        }

        if (!incidence) {
            return false;
        }

        const Attendee myself = findMyself(incidence, receiver);

        // find our delegator, we need to inform him as well
        QString delegator;
        if (status != Attendee::NeedsAction && !myself.isNull() && !myself.delegator().isEmpty()) {
            const Attendee::List attendees = incidence->attendees();
            Attendee::List::ConstIterator end = attendees.constEnd();
            for (Attendee::List::ConstIterator it = attendees.constBegin();
                 it != end; ++it) {
                if (KEmailAddress::compareEmail((*it).fullName(), myself.delegator(), false)
                    && (*it).status() == Attendee::Delegated) {
                    delegator = (*it).fullName();
                    delegatorRSVP = (*it).RSVP();
                    break;
                }
            }
        }

        if (status != Attendee::NeedsAction && ((!myself.isNull() && (myself.RSVP() || myself.status() == Attendee::NeedsAction)) || heuristicalRSVP(incidence))) {
            Attendee newMyself = setStatusOnMyself(incidence, myself, status, receiver);
            if (!newMyself.isNull() && status == Attendee::Delegated) {
                newMyself.setDelegate(delegateString);
                newMyself.setRSVP(delegatorRSVP);
            }
            ok = mail(viewerInstance, incidence, dir, iTIPReply, receiver);

            // check if we need to inform our delegator about this as well
            if (!newMyself.isNull()
                && (status == Attendee::Accepted || status == Attendee::Declined)
                && !delegator.isEmpty()) {
                if (delegatorRSVP || status == Attendee::Declined) {
                    ok = mail(viewerInstance, incidence, dir, iTIPReply, receiver, delegator);
                }
            }
        } else if (myself.isNull() && (status != Attendee::Declined && status != Attendee::NeedsAction)) {
            // forwarded invitation
            QString name;
            QString email;
            KEmailAddress::extractEmailAddressAndName(receiver, email, name);
            if (!email.isEmpty()) {
                Attendee newMyself(name, email, true,  // RSVP, otherwise we would not be here
                                 status,
                                 heuristicalRole(incidence),
                                 QString());
                incidence->clearAttendees();
                incidence->addAttendee(newMyself);
                ok = mail(viewerInstance, incidence, dir, iTIPReply, receiver);
            }
        } else {
            if (MessageViewer::MessageViewerSettings::self()->deleteInvitationEmailsAfterSendingReply()) {
                viewerInstance->deleteMessage();
            }
        }

        // create invitation for the delegate (same as the original invitation
        // with the delegate as additional attendee), we also use that for updating
        // our calendar
        if (status == Attendee::Delegated) {
            incidence = stringToIncidence(iCal);
            auto attendees = incidence->attendees();
            const int myselfIdx = findMyself(attendees, receiver);
            if (myselfIdx >= 0) {
                attendees[myselfIdx].setStatus(status);
                attendees[myselfIdx].setDelegate(delegateString);
                incidence->setAttendees(attendees);
            }
            QString name, email;
            KEmailAddress::extractEmailAddressAndName(delegateString, email, name);
            Attendee delegate(name, email, true);
            delegate.setDelegator(receiver);
            incidence->addAttendee(delegate);

            ICalFormat format;
            format.setTimeZone(QTimeZone::systemTimeZone());
            const QString iCal = format.createScheduleMessage(incidence, iTIPRequest);
            if (!saveFile(receiver, iCal, dir, part)) {
                return false;
            }

            ok = mail(viewerInstance, incidence, dir, iTIPRequest, receiver, delegateString, Delegation);
        }
        return ok;
    }

    bool openAttachment(const QString &name, const QString &iCal) const
    {
        Attachment attachment(findAttachment(name, iCal));
        if (attachment.isEmpty()) {
            return false;
        }

        if (attachment.isUri()) {
            QDesktopServices::openUrl(QUrl(attachment.uri()));
        } else {
            // put the attachment in a temporary file and launch it
            QTemporaryFile *file = nullptr;
            QMimeDatabase db;
            QStringList patterns = db.mimeTypeForName(attachment.mimeType()).globPatterns();
            if (!patterns.empty()) {
                QString pattern = patterns.at(0);
                file = new QTemporaryFile(QDir::tempPath() + QStringLiteral("/messageviewer_XXXXXX") + pattern.remove(QLatin1Char('*')));
            } else {
                file = new QTemporaryFile();
            }
            file->setAutoRemove(false);
            file->open();
            file->setPermissions(QFile::ReadUser);
            file->write(QByteArray::fromBase64(attachment.data()));
            file->close();

            KRun::RunFlags flags;
            flags |= KRun::DeleteTemporaryFiles;
            bool stat = KRun::runUrl(QUrl::fromLocalFile(file->fileName()), attachment.mimeType(), nullptr, flags);
            delete file;
            return stat;
        }
        return true;
    }

    bool saveAsAttachment(const QString &name, const QString &iCal) const
    {
        Attachment a(findAttachment(name, iCal));
        if (a.isEmpty()) {
            return false;
        }

        // get the saveas file name
        const QString saveAsFile = QFileDialog::getSaveFileName(nullptr, i18n("Save Invitation Attachment"), name, QString());

        if (saveAsFile.isEmpty()) {
            return false;
        }

        bool stat = false;
        if (a.isUri()) {
            // save the attachment url
            auto job = KIO::file_copy(QUrl(a.uri()), QUrl::fromLocalFile(saveAsFile));
            stat = job->exec();
        } else {
            // put the attachment in a temporary file and save it
            QTemporaryFile *file{
                nullptr
            };
            QMimeDatabase db;
            QStringList patterns = db.mimeTypeForName(a.mimeType()).globPatterns();
            if (!patterns.empty()) {
                QString pattern = patterns.at(0);
                file = new QTemporaryFile(QDir::tempPath() + QStringLiteral("/messageviewer_XXXXXX") + pattern.remove(QLatin1Char('*')));
            } else {
                file = new QTemporaryFile();
            }
            file->setAutoRemove(false);
            file->open();
            file->setPermissions(QFile::ReadUser);
            file->write(QByteArray::fromBase64(a.data()));
            file->close();
            const QString filename = file->fileName();
            delete file;

            auto job = KIO::file_copy(QUrl::fromLocalFile(filename), QUrl::fromLocalFile(saveAsFile));
            stat = job->exec();
        }
        return stat;
    }

    bool ensureKorganizerRunning(bool switchTo) const
    {
        // FIXME: this function should be inside a QObject, and async,
        //         and Q_EMIT a signal when korg registered itself successfully

        // Or better, use DBus activation in all cases.

        QString error;
        bool result = true;
        QString dbusService;

#if defined(Q_OS_WIN32)
        //Can't run the korganizer-mobile.sh through KDBusServiceStarter in these platforms.
        QDBusInterface *interface = new QDBusInterface(QLatin1String("org.kde.korganizer"), QStringLiteral("/MainApplication"));
        if (!interface->isValid()) {
            qCDebug(TEXT_CALENDAR_LOG) << "Starting korganizer...";

            QDBusServiceWatcher *watcher
                = new QDBusServiceWatcher(QLatin1String("org.kde.korganizer"), QDBusConnection::sessionBus(),
                                          QDBusServiceWatcher::WatchForRegistration);
            QEventLoop loop;
            watcher->connect(watcher, &QDBusServiceWatcher::serviceRegistered, &loop, &QEventLoop::quit);
            result = QProcess::startDetached(QLatin1String("korganizer"));
            if (result) {
                qCDebug(TEXT_CALENDAR_LOG) << "Starting loop";
                loop.exec();
                qCDebug(TEXT_CALENDAR_LOG) << "Korganizer finished starting";
            } else {
                qCWarning(TEXT_CALENDAR_LOG) << "Failed to start korganizer with QProcess";
            }

            delete watcher;
        }
        delete interface;
#else
        QString constraint;

        result = KDBusServiceStarter::self()->findServiceFor(QStringLiteral("DBUS/Organizer"),
                                                             constraint,
                                                             &error, &dbusService) == 0;
#endif
        if (result) {
            // OK, so korganizer (or kontact) is running. Now ensure the object we want is loaded.
            QDBusInterface iface(QStringLiteral("org.kde.korganizer"), QStringLiteral("/MainApplication"),
                                 QStringLiteral("org.kde.PIMUniqueApplication"));
            if (iface.isValid()) {
                if (switchTo) {
                    iface.call(QStringLiteral("newInstance"));   // activate korganizer window
                }
#if 0 //Not exist
                QDBusInterface pimIface("org.kde.korganizer", "/korganizer_PimApplication",
                                        "org.kde.PIMUniqueApplication");
                QDBusReply<bool> r = pimIface.call("load");
                if (!r.isValid() || !r.value()) {
                    qCWarning(TEXT_CALENDAR_LOG) << "Loading korganizer failed: " << pimIface.lastError().message();
                }
#endif
            } else {
                qCWarning(TEXT_CALENDAR_LOG) << "Couldn't obtain korganizer D-Bus interface" << iface.lastError().message();
            }

            // We don't do anything with it, we just need it to be running so that it handles
            // the incoming directory.
        } else {
            qCWarning(TEXT_CALENDAR_LOG) << "Couldn't start DBUS/Organizer:" << dbusService << error;
        }
        return result;
    }

    void showCalendar(const QDate &date) const
    {
        if (ensureKorganizerRunning(true)) {
            QDBusInterface *kontact
                = new QDBusInterface(QStringLiteral("org.kde.kontact"), QStringLiteral("/KontactInterface"),
                                     QStringLiteral("org.kde.kontact.KontactInterface"), QDBusConnection::sessionBus());
            if (kontact->isValid()) {
                kontact->call(QStringLiteral("selectPlugin"), QStringLiteral("kontact_korganizerplugin"));
            }
            delete kontact;

            OrgKdeKorganizerCalendarInterface *iface
                = new OrgKdeKorganizerCalendarInterface(QStringLiteral("org.kde.korganizer"), QStringLiteral("/Calendar"),
                                                        QDBusConnection::sessionBus(), nullptr);
            if (!iface->isValid()) {
                qCDebug(TEXT_CALENDAR_LOG) << "Calendar interface is not valid! " << iface->lastError().message();
                delete iface;
                return;
            }
            iface->showEventView();
            iface->showDate(date);
            delete iface;
        }
    }

    bool handleIgnore(Viewer *viewerInstance) const
    {
        // simply move the message to trash
        viewerInstance->deleteMessage();
        return true;
    }

    bool handleDeclineCounter(const QString &iCal, MimeTreeParser::Interface::BodyPart *part, Viewer *viewerInstance) const
    {
        const QString receiver(findReceiver(part->content()));
        if (receiver.isEmpty()) {
            return true;
        }
        Incidence::Ptr incidence(stringToIncidence(iCal));
        if (askForComment(Attendee::Declined)) {
            QPointer<ReactionToInvitationDialog> dlg = new ReactionToInvitationDialog(nullptr);
            dlg->setWindowTitle(i18n("Decline Counter Proposal"));
            QString comment;
            if (dlg->exec()) {
                comment = dlg->comment();
                delete dlg;
            } else {
                delete dlg;
                return true;
            }

            if (comment.trimmed().isEmpty()) {
                KMessageBox::error(
                    nullptr,
                    i18n("You forgot to add proposal. Please add it. Thanks"));
                return true;
            } else {
                incidence->addComment(comment);
            }
        }
        return mail(viewerInstance, incidence, QStringLiteral("declinecounter"), KCalCore::iTIPDeclineCounter,
                    receiver, QString(), DeclineCounter);
    }

    bool counterProposal(const QString &iCal, MimeTreeParser::Interface::BodyPart *part) const
    {
        const QString receiver = findReceiver(part->content());
        if (receiver.isEmpty()) {
            return true;
        }

        // Don't delete the invitation here in any case, if the counter proposal
        // is declined you might need it again.
        return saveFile(receiver, iCal, QStringLiteral("counter"), part);
    }

    bool handleClick(Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const override
    {
        // filter out known paths that don't belong to this type of urlmanager.
        // kolab/issue4054 msg27201
        if (path.contains(QLatin1String("addToAddressBook:")) || path.contains(QLatin1String("updateToAddressBook"))) {
            return false;
        }

        if (!hasMyWritableEventsFolders(QStringLiteral("calendar"))) {
            KMessageBox::error(
                nullptr,
                i18n("You have no writable calendar folders for invitations, "
                     "so storing or saving a response will not be possible.\n"
                     "Please create at least 1 writable events calendar and re-sync."));
            return false;
        }

        // If the bodypart does not have a charset specified, we need to fall back to utf8,
        // not the KMail fallback encoding, so get the contents as binary and decode explicitly.
        QString iCal;
        if (!part->content()->contentType()->hasParameter(QStringLiteral("charset"))) {
            const QByteArray &ba = part->content()->decodedContent();
            iCal = QString::fromUtf8(ba);
        } else {
            iCal = part->content()->decodedText();
        }

        Incidence::Ptr incidence = stringToIncidence(iCal);
        if (!incidence) {
            KMessageBox::sorry(
                nullptr,
                i18n("The calendar invitation stored in this email message is broken in some way. "
                     "Unable to continue."));
            return false;
        }

        bool result = false;
        if (cancelPastInvites(incidence, path)) {
            return result;
        }

        if (path == QLatin1String("accept")) {
            result = handleInvitation(iCal, Attendee::Accepted, part, viewerInstance);
        } else if (path == QLatin1String("accept_conditionally")) {
            result = handleInvitation(iCal, Attendee::Tentative, part, viewerInstance);
        } else if (path == QLatin1String("counter")) {
            result = counterProposal(iCal, part);
        } else if (path == QLatin1String("ignore")) {
            result = handleIgnore(viewerInstance);
        } else if (path == QLatin1String("decline")) {
            result = handleInvitation(iCal, Attendee::Declined, part, viewerInstance);
        } else if (path == QLatin1String("decline_counter")) {
            result = handleDeclineCounter(iCal, part, viewerInstance);
        } else if (path == QLatin1String("postpone")) {
            result = handleInvitation(iCal, Attendee::NeedsAction, part, viewerInstance);
        } else if (path == QLatin1String("delegate")) {
            result = handleInvitation(iCal, Attendee::Delegated, part, viewerInstance);
        } else if (path == QLatin1String("forward")) {
            AttendeeSelector dlg;
            if (dlg.exec() == QDialog::Rejected) {
                return true;
            }
            QString fwdTo = dlg.attendees().join(QStringLiteral(", "));
            if (fwdTo.isEmpty()) {
                return true;
            }
            const QString receiver = findReceiver(part->content());
            result = mail(viewerInstance, incidence, QStringLiteral("forward"), iTIPRequest, receiver, fwdTo, Forward);
        } else if (path == QLatin1String("check_calendar")) {
            incidence = stringToIncidence(iCal);
            showCalendar(incidence->dtStart().date());
            return true;
        } else if (path == QLatin1String("reply") || path == QLatin1String("cancel") || path == QLatin1String("accept_counter")) {
            // These should just be saved with their type as the dir
            const QString p = (path == QLatin1String("accept_counter") ? QStringLiteral("reply") : path);
            if (saveFile(QStringLiteral("Receiver Not Searched"), iCal, p, part)) {
                if (MessageViewer::MessageViewerSettings::self()->deleteInvitationEmailsAfterSendingReply()) {
                    viewerInstance->deleteMessage();
                }
                result = true;
            }
        } else if (path == QLatin1String("record")) {
            incidence = stringToIncidence(iCal);
            QString summary;
            int response
                = KMessageBox::questionYesNoCancel(
                      nullptr,
                      i18nc("@info",
                            "The organizer is not expecting a reply to this invitation "
                            "but you can send them an email message if you desire.\n\n"
                            "Would you like to send the organizer a message regarding this invitation?\n"
                            "Press the [Cancel] button to cancel the recording operation."),
                      i18nc("@title:window", "Send Email to Organizer"),
                      KGuiItem(i18n("Do Not Send")),
                      KGuiItem(i18n("Send EMail")));

            switch (response) {
            case KMessageBox::Cancel:
                break;
            case KMessageBox::No:
            {                       // means "send email"
                summary = incidence->summary();
                if (!summary.isEmpty()) {
                    summary = i18n("Re: %1", summary);
                }

                QUrlQuery query;
                query.addQueryItem(QStringLiteral("to"), incidence->organizer().email());
                query.addQueryItem(QStringLiteral("subject"), summary);
                QUrl url;
                url.setScheme(QStringLiteral("mailto"));
                url.setQuery(query);
                QDesktopServices::openUrl(url);
            }
            //fall through
            case KMessageBox::Yes: // means "do not send"
                if (saveFile(QStringLiteral("Receiver Not Searched"), iCal, QStringLiteral("reply"), part)) {
                    if (MessageViewer::MessageViewerSettings::self()->deleteInvitationEmailsAfterSendingReply()) {
                        viewerInstance->deleteMessage();
                        result = true;
                    }
                }
                showCalendar(incidence->dtStart().date());
                break;
            }
        } else if (path == QLatin1String("delete")) {
            viewerInstance->deleteMessage();
            result = true;
        }

        if (path.startsWith(QLatin1String("ATTACH:"))) {
            const QString name = QString::fromUtf8(QByteArray::fromBase64(path.mid(7).toUtf8()));
            result = openAttachment(name, iCal);
        }

        if (result) {
            // do not close the secondary window if an attachment was opened (kolab/issue4317)
            if (!path.startsWith(QLatin1String("ATTACH:"))) {
                qCDebug(TEXT_CALENDAR_LOG) << "AKONADI PORT: Disabled code in " << Q_FUNC_INFO << "about closing if in a secondary window";
#if 0 // TODO port to Akonadi
                c.closeIfSecondaryWindow();
#endif
            }
        }
        return result;
    }

    bool handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &point) const override
    {
        QString name = path;
        if (path.startsWith(QLatin1String("ATTACH:"))) {
            name = QString::fromUtf8(QByteArray::fromBase64(path.mid(7).toUtf8()));
        } else {
            return false; //because it isn't an attachment invitation
        }

        QString iCal;
        if (!part->content()->contentType()->hasParameter(QStringLiteral("charset"))) {
            const QByteArray &ba = part->content()->decodedContent();
            iCal = QString::fromUtf8(ba);
        } else {
            iCal = part->content()->decodedText();
        }

        QMenu *menu = new QMenu();
        QAction *open
            = menu->addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("Open Attachment"));
        QAction *saveas
            = menu->addAction(QIcon::fromTheme(QStringLiteral("document-save-as")), i18n("Save Attachment As..."));

        QAction *a = menu->exec(point, nullptr);
        if (a == open) {
            openAttachment(name, iCal);
        } else if (a == saveas) {
            saveAsAttachment(name, iCal);
        }
        delete menu;
        return true;
    }

    QString statusBarMessage(MimeTreeParser::Interface::BodyPart *, const QString &path) const override
    {
        if (!path.isEmpty()) {
            if (path == QLatin1String("accept")) {
                return i18n("Accept invitation");
            } else if (path == QLatin1String("accept_conditionally")) {
                return i18n("Accept invitation conditionally");
            } else if (path == QLatin1String("accept_counter")) {
                return i18n("Accept counter proposal");
            } else if (path == QLatin1String("counter")) {
                return i18n("Create a counter proposal...");
            } else if (path == QLatin1String("ignore")) {
                return i18n("Throw mail away");
            } else if (path == QLatin1String("decline")) {
                return i18n("Decline invitation");
            } else if (path == QLatin1String("postpone")) {
                return i18n("Postpone");
            } else if (path == QLatin1String("decline_counter")) {
                return i18n("Decline counter proposal");
            } else if (path == QLatin1String("check_calendar")) {
                return i18n("Check my calendar...");
            } else if (path == QLatin1String("reply")) {
                return i18n("Record response into my calendar");
            } else if (path == QLatin1String("record")) {
                return i18n("Record invitation into my calendar");
            } else if (path == QLatin1String("delete")) {
                return i18n("Move this invitation to my trash folder");
            } else if (path == QLatin1String("delegate")) {
                return i18n("Delegate invitation");
            } else if (path == QLatin1String("forward")) {
                return i18n("Forward invitation");
            } else if (path == QLatin1String("cancel")) {
                return i18n("Remove invitation from my calendar");
            } else if (path.startsWith(QLatin1String("ATTACH:"))) {
                const QString name = QString::fromUtf8(QByteArray::fromBase64(path.mid(7).toUtf8()));
                return i18n("Open attachment \"%1\"", name);
            }
        }

        return QString();
    }

    bool askForComment(Attendee::PartStat status) const
    {
        if (status != Attendee::NeedsAction && ((status != Attendee::Accepted
                                                 && MessageViewer::MessageViewerSettings::self()->askForCommentWhenReactingToInvitation()
                                                 == MessageViewer::MessageViewerSettings::EnumAskForCommentWhenReactingToInvitation::AskForAllButAcceptance)
                                                || (MessageViewer::MessageViewerSettings::self()->askForCommentWhenReactingToInvitation()
                                                    == MessageViewer::MessageViewerSettings::EnumAskForCommentWhenReactingToInvitation::AlwaysAsk))) {
            return true;
        }
        return false;
    }
};

class Plugin : public QObject, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "text_calendar.json")
public:
    MessageViewer::MessagePartRendererBase *renderer(int idx) override
    {
        if (idx < 2) {
            return new Formatter();
        } else {
            return nullptr;
        }
    }

    const MessageViewer::Interface::BodyPartURLHandler *urlHandler(int idx) const override
    {
        if (idx == 0) {
            return new UrlHandler();
        } else {
            return nullptr;
        }
    }
};
}

#include "text_calendar.moc"

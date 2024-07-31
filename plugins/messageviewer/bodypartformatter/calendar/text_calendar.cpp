/*
  This file is part of kdepim.

  SPDX-FileCopyrightText: 2004 Cornelius Schumacher <schumacher@kde.org>
  SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>
  SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>
  SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "attendeeselector.h"
#include "calendarinterface.h"
#include "delegateselector.h"
#include "memorycalendarmemento.h"
#include "reactiontoinvitationdialog.h"
#include "syncitiphandler.h"

#include <KIdentityManagementCore/IdentityManager>

#include <MessageViewer/BodyPartURLHandler>
#include <MessageViewer/HtmlWriter>
#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessageViewerSettings>
#include <MessageViewer/Viewer>
#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/MessagePart>
using namespace MessageViewer;

#include <KCalendarCore/ICalFormat>
using namespace KCalendarCore;

#include <KCalUtils/IncidenceFormatter>

#include <KMime/Message>

#include <KIdentityManagementCore/Identity>

#include <KEmailAddress>

#include <Akonadi/MessageQueueJob>
#include <MailTransport/TransportManager>

#include "text_calendar_debug.h"

#include <KIO/FileCopyJob>
#include <KIO/JobUiDelegate>
#include <KIO/OpenUrlJob>
#include <KIO/StatJob>
#include <KLocalizedString>
#include <KMessageBox>

#include <QDBusServiceWatcher>
#include <QDesktopServices>
#include <QFileDialog>
#include <QIcon>
#include <QInputDialog>
#include <QMenu>
#include <QMimeDatabase>
#include <QPointer>
#include <QTemporaryFile>
#include <QUrl>

using namespace MailTransport;

namespace
{
static bool hasMyWritableEventsFolders(const QString &family)
{
    Q_UNUSED(family)
#if 0 // TODO port to Akonadi
    QString myfamily = family;
    if (family.isEmpty()) {
        myfamily = QStringLiteral("calendar");
    }

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
    KMInvitationFormatterHelper(const MimeTreeParser::MessagePartPtr &bodyPart, const KCalendarCore::MemoryCalendar::Ptr &calendar)
        : mBodyPart(bodyPart)
        , mCalendar(calendar)
    {
    }

    QString generateLinkURL(const QString &id) override
    {
        return mBodyPart->makeLink(id);
    }

    [[nodiscard]] KCalendarCore::Calendar::Ptr calendar() const override
    {
        return mCalendar;
    }

private:
    const MimeTreeParser::MessagePartPtr mBodyPart;
    const KCalendarCore::MemoryCalendar::Ptr mCalendar;
};

static QString getSender(const MimeTreeParser::MessagePart *msgPart)
{
    if (auto msg = dynamic_cast<KMime::Message *>(msgPart->content()->topLevel()); msg != nullptr) {
        return msg->sender()->asUnicodeString();
    }
    return {};
}

class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *writer, MessageViewer::RenderContext *) const override
    {
        QMimeDatabase db;
        auto mt = db.mimeTypeForName(QString::fromLatin1(msgPart->content()->contentType()->mimeType().toLower()));
        if (!mt.isValid() || mt.name() != QLatin1StringView("text/calendar")) {
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
        auto memento = dynamic_cast<MemoryCalendarMemento *>(msgPart->memento());

        if (memento) {
            if (memento->finished()) {
                KMInvitationFormatterHelper helper(msgPart, memento->calendar());
                QString source;
                // If the bodypart does not have a charset specified, we need to fall back to utf8,
                // not the KMail fallback encoding, so get the contents as binary and decode explicitly.
                if (msgPart->content()->contentType()->parameter("charset").isEmpty()) {
                    const QByteArray &ba = msgPart->content()->decodedContent();
                    source = QString::fromUtf8(ba);
                } else {
                    source = msgPart->text();
                }

                MemoryCalendar::Ptr cl(new MemoryCalendar(QTimeZone::systemTimeZone()));

                const auto sender = getSender(msgPart.get());
                const QString html = KCalUtils::IncidenceFormatter::formatICalInvitationNoHtml(source, cl, &helper, sender);

                if (html.isEmpty()) {
                    return false;
                }
                writer->write(html);
            }
        } else {
            auto memento = new MemoryCalendarMemento();
            msgPart->setMemento(memento);
            QObject::connect(memento, &MemoryCalendarMemento::update, nodeHelper, &MimeTreeParser::NodeHelper::update);
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
        // TODO: Error message?
        qCWarning(TEXT_CALENDAR_LOG) << "Can't parse this ical string: " << iCal;
        return {};
    }

    return message->event().dynamicCast<Incidence>();
}

class UrlHandler : public MessageViewer::Interface::BodyPartURLHandler
{
public:
    UrlHandler()
    {
        // qCDebug(TEXT_CALENDAR_LOG) << "UrlHandler() (iCalendar)";
    }

    [[nodiscard]] QString name() const override
    {
        return QStringLiteral("calendar handler");
    }

    [[nodiscard]] Attendee findMyself(const Incidence::Ptr &incidence, const QString &receiver) const
    {
        const Attendee::List attendees = incidence->attendees();
        const auto idx = findMyself(attendees, receiver);
        if (idx >= 0) {
            return attendees.at(idx);
        }
        return {};
    }

    [[nodiscard]] int findMyself(const Attendee::List &attendees, const QString &receiver) const
    {
        // Find myself. There will always be all attendees listed, even if
        // only I need to answer it.
        for (int i = 0; i < attendees.size(); ++i) {
            // match only the email part, not the name
            if (KEmailAddress::compareEmail(attendees.at(i).email(), receiver, false)) {
                // We are the current one, and even the receiver, note
                // this and quit searching.
                return i;
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
            KMessageBox::error(nullptr, i18n("No attachment named \"%1\" found in the invitation.", name));
            return Attachment();
        }

        if (attachment.isUri()) {
            bool fileExists = false;
            QUrl attachmentUrl(attachment.uri());
            if (attachmentUrl.isLocalFile()) {
                fileExists = QFile::exists(attachmentUrl.toLocalFile());
            } else {
                auto job = KIO::stat(attachmentUrl, KIO::StatJob::SourceSide, KIO::StatBasic);
                fileExists = job->exec();
            }
            if (!fileExists) {
                KMessageBox::information(nullptr,
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
            return {};
        }

        QString receiver;
        KIdentityManagementCore::IdentityManager *im = KIdentityManagementCore::IdentityManager::self();

        KMime::Types::Mailbox::List addrs;
        if (auto header = node->topLevel()->header<KMime::Headers::To>()) {
            addrs = header->mailboxes();
        }
        int found = 0;
        QList<KMime::Types::Mailbox>::const_iterator end = addrs.constEnd();
        for (QList<KMime::Types::Mailbox>::const_iterator it = addrs.constBegin(); it != end; ++it) {
            if (im->identityForAddress(QLatin1StringView((*it).address())) != KIdentityManagementCore::Identity::null()) {
                // Ok, this could be us
                ++found;
                receiver = QLatin1StringView((*it).address());
            }
        }

        KMime::Types::Mailbox::List ccaddrs;
        if (auto header = node->topLevel()->header<KMime::Headers::Cc>()) {
            ccaddrs = header->mailboxes();
        }
        end = ccaddrs.constEnd();
        for (QList<KMime::Types::Mailbox>::const_iterator it = ccaddrs.constBegin(); it != end; ++it) {
            if (im->identityForAddress(QLatin1StringView((*it).address())) != KIdentityManagementCore::Identity::null()) {
                // Ok, this could be us
                ++found;
                receiver = QLatin1StringView((*it).address());
            }
        }
        if (found != 1) {
            QStringList possibleAddrs;
            bool ok;
            QString selectMessage;
            if (found == 0) {
                selectMessage = i18n(
                    "<qt>None of your identities match the receiver of this message,<br/>"
                    "please choose which of the following addresses is yours,<br/> if any, "
                    "or select one of your identities to use in the reply:</qt>");
                possibleAddrs += im->allEmails();
            } else {
                selectMessage = i18n(
                    "<qt>Several of your identities match the receiver of this message,<br/>"
                    "please choose which of the following addresses is yours:</qt>");
                possibleAddrs.reserve(addrs.count() + ccaddrs.count());
                for (const KMime::Types::Mailbox &mbx : std::as_const(addrs)) {
                    possibleAddrs.append(QLatin1StringView(mbx.address()));
                }
                for (const KMime::Types::Mailbox &mbx : std::as_const(ccaddrs)) {
                    possibleAddrs.append(QLatin1StringView(mbx.address()));
                }
            }

            // select default identity by default
            const QString defaultAddr = im->defaultIdentity().primaryEmailAddress();
            const int defaultIndex = qMax(0, possibleAddrs.indexOf(defaultAddr));

            receiver = QInputDialog::getItem(nullptr, i18n("Select Address"), selectMessage, possibleAddrs, defaultIndex, false, &ok);

            if (!ok) {
                receiver.clear();
            }
        }
        return receiver;
    }

    [[nodiscard]] Attendee setStatusOnMyself(const Incidence::Ptr &incidence, const Attendee &myself, Attendee::PartStat status, const QString &receiver) const
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
        Q_ASSERT(!email.isEmpty()); // delivery must be possible

        Attendee newMyself(name,
                           email,
                           true, // RSVP, otherwise we would not be here
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
        DeclineCounter,
    };

    bool mailICal(const QString &receiver,
                  const QString &to,
                  const QString &iCal,
                  const QString &subject,
                  const QString &status,
                  bool delMessage,
                  Viewer *viewerInstance) const
    {
        qCDebug(TEXT_CALENDAR_LOG) << "Mailing message:" << iCal;

        KMime::Message::Ptr msg(new KMime::Message);
        if (MessageViewer::MessageViewerSettings::self()->exchangeCompatibleInvitations()) {
            msg->subject()->fromUnicodeString(status);
            QString tsubject = subject;
            tsubject.remove(i18n("Answer: "));
            if (status == QLatin1StringView("cancel")) {
                msg->subject()->fromUnicodeString(i18nc("Not able to attend.", "Declined: %1", tsubject));
            } else if (status == QLatin1StringView("tentative")) {
                msg->subject()->fromUnicodeString(i18nc("Unsure if it is possible to attend.", "Tentative: %1", tsubject));
            } else if (status == QLatin1StringView("accepted")) {
                msg->subject()->fromUnicodeString(i18nc("Accepted the invitation.", "Accepted: %1", tsubject));
            } else {
                msg->subject()->fromUnicodeString(subject);
            }
        } else {
            msg->subject()->fromUnicodeString(subject);
        }
        msg->to()->fromUnicodeString(to);
        msg->from()->fromUnicodeString(receiver);
        msg->date()->setDateTime(QDateTime::currentDateTime());

        if (MessageViewer::MessageViewerSettings::self()->legacyBodyInvites()) {
            auto ct = msg->contentType(); // create
            ct->setMimeType("text/calendar");
            ct->setCharset("utf-8");
            ct->setName(QStringLiteral("cal.ics"));
            ct->setParameter(QByteArrayLiteral("method"), QStringLiteral("reply"));

            auto disposition = new KMime::Headers::ContentDisposition;
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

            // Set the first multipart, the body message.
            auto bodyMessage = new KMime::Content;
            auto bodyDisposition = new KMime::Headers::ContentDisposition;
            bodyDisposition->setDisposition(KMime::Headers::CDinline);
            auto bodyMessageCt = bodyMessage->contentType();
            bodyMessageCt->setMimeType("text/plain");
            bodyMessageCt->setCharset("utf-8");
            bodyMessage->contentTransferEncoding()->setEncoding(KMime::Headers::CEquPr);
            const QString answer = i18n("Invitation answer attached.");
            bodyMessage->setBody(answer.toUtf8());
            bodyMessage->setHeader(bodyDisposition);
            msg->appendContent(bodyMessage);

            // Set the second multipart, the attachment.
            auto attachMessage = new KMime::Content;
            auto attachDisposition = new KMime::Headers::ContentDisposition;
            attachDisposition->setDisposition(KMime::Headers::CDattachment);
            auto attachCt = attachMessage->contentType();
            attachCt->setMimeType("text/calendar");
            attachCt->setCharset("utf-8");
            attachCt->setName(QStringLiteral("cal.ics"));
            attachCt->setParameter(QByteArrayLiteral("method"), QStringLiteral("reply"));
            attachMessage->setHeader(attachDisposition);
            attachMessage->contentTransferEncoding()->setEncoding(KMime::Headers::CEquPr);
            attachMessage->setBody(KMime::CRLFtoLF(iCal.toUtf8()));
            msg->appendContent(attachMessage);
        }

        // Try and match the receiver with an identity.
        // Setting the identity here is important, as that is used to select the correct
        // transport later
        KIdentityManagementCore::IdentityManager *im = KIdentityManagementCore::IdentityManager::self();
        const KIdentityManagementCore::Identity identity = im->identityForAddress(findReceiver(viewerInstance->message().data()));

        const bool nullIdentity = (identity == KIdentityManagementCore::Identity::null());

        if (!nullIdentity) {
            auto x_header = new KMime::Headers::Generic("X-KMail-Identity");
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
        header->fromUnicodeString(QString::number(transportId));
        msg->setHeader(header);

        // Outlook will only understand the reply if the From: header is the
        // same as the To: header of the invitation message.
        if (!MessageViewer::MessageViewerSettings::self()->legacyMangleFromToHeaders()) {
            if (identity != KIdentityManagementCore::Identity::null()) {
                msg->from()->fromUnicodeString(identity.fullEmailAddr());
            }
            // Remove BCC from identity on ical invitations (kolab/issue474)
            msg->removeHeader<KMime::Headers::Bcc>();
        }

        msg->assemble();
        MailTransport::Transport *transport = MailTransport::TransportManager::self()->transportById(transportId);

        auto job = new Akonadi::MessageQueueJob;

        job->addressAttribute().setTo(QStringList() << KEmailAddress::extractEmailAddress(KEmailAddress::normalizeAddressesAndEncodeIdn(to)));
        job->transportAttribute().setTransportId(transport->id());

        if (transport->specifySenderOverwriteAddress()) {
            job->addressAttribute().setFrom(
                KEmailAddress::extractEmailAddress(KEmailAddress::normalizeAddressesAndEncodeIdn(transport->senderOverwriteAddress())));
        } else {
            job->addressAttribute().setFrom(KEmailAddress::extractEmailAddress(KEmailAddress::normalizeAddressesAndEncodeIdn(msg->from()->asUnicodeString())));
        }

        job->setMessage(msg);

        if (!job->exec()) {
            qCWarning(TEXT_CALENDAR_LOG) << "Error queuing message in outbox:" << job->errorText();
            return false;
        }
        // We are not notified when mail was sent, so assume it was sent when queued.
        if (delMessage && MessageViewer::MessageViewerSettings::self()->deleteInvitationEmailsAfterSendingReply()) {
            viewerInstance->deleteMessage();
        }
        return true;
    }

    bool mail(Viewer *viewerInstance,
              const Incidence::Ptr &incidence,
              const QString &status,
              iTIPMethod method = iTIPReply,
              const QString &receiver = QString(),
              const QString &to = QString(),
              MailType type = Answer) const
    {
        // status is accepted/tentative/declined
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
            QString tname;
            QString temail;
            KMime::Message::Ptr message = viewerInstance->message();
            KEmailAddress::extractEmailAddressAndName(message->sender()->asUnicodeString(), temail, tname);
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
        auto memento = dynamic_cast<MemoryCalendarMemento *>(bodyPart->memento());
        // This will block. There's no way to make it async without refactoring the memento mechanism

        auto itipHandler = new SyncItipHandler(receiver, iCal, type, memento->calendar());

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

    [[nodiscard]] bool cancelPastInvites(const Incidence::Ptr incidence, const QString &path) const
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
                    warnStr = i18n("\"%1\", happening all day today, is currently in-progress.", event->summary());
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
                    } else if (todo->hasStartDate() && todo->dtStart().date() <= today && today <= todo->dtDue().date()) {
                        warnStr = i18n("\"%1\", happening all-day today, is currently in-progress.", todo->summary());
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
            KGuiItem yesItem;
            KGuiItem noItem;
            if (path == QLatin1StringView("accept")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to accept the task?");
                } else {
                    queryStr = i18n("Do you still want to accept the invitation?");
                }
                yesItem.setText(i18nc("@action:button", "Accept"));
                yesItem.setIconName(QStringLiteral("dialog-ok"));
            } else if (path == QLatin1StringView("accept_conditionally")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to send conditional acceptance of the invitation?");
                } else {
                    queryStr = i18n("Do you still want to send conditional acceptance of the task?");
                }
                yesItem.setText(i18nc("@action:button", "Send"));
                yesItem.setIconName(QStringLiteral("mail-send"));
            } else if (path == QLatin1StringView("accept_counter")) {
                queryStr = i18n("Do you still want to accept the counter proposal?");
                yesItem.setText(i18nc("@action:button", "Accept"));
                yesItem.setIconName(QStringLiteral("dialog-ok"));
            } else if (path == QLatin1StringView("counter")) {
                queryStr = i18n("Do you still want to send a counter proposal?");
                yesItem.setText(i18nc("@action:button", "Send"));
                yesItem.setIconName(QStringLiteral("mail-send"));
            } else if (path == QLatin1StringView("decline")) {
                queryStr = i18n("Do you still want to send a decline response?");
                yesItem.setText(i18nc("@action:button", "Send"));
                yesItem.setIconName(QStringLiteral("mail-send"));
            } else if (path == QLatin1StringView("decline_counter")) {
                queryStr = i18n("Do you still want to decline the counter proposal?");
                yesItem.setText(i18nc("@action:button", "Decline"));
            } else if (path == QLatin1StringView("reply")) {
                queryStr = i18n("Do you still want to record this response in your calendar?");
                yesItem.setText(i18nc("@action:button", "Record"));
            } else if (path == QLatin1StringView("delegate")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to delegate this task?");
                } else {
                    queryStr = i18n("Do you still want to delegate this invitation?");
                }
                yesItem.setText(i18nc("@action:button", "Delegate"));
            } else if (path == QLatin1StringView("forward")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to forward this task?");
                } else {
                    queryStr = i18n("Do you still want to forward this invitation?");
                }
                yesItem.setText(i18nc("@action:button", "Forward"));
                yesItem.setIconName(QStringLiteral("mail-forward"));
            } else if (path == QLatin1StringView("cancel")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to cancel this task?");
                    yesItem.setText(i18nc("@action:button", "Cancel Task"));
                } else {
                    queryStr = i18n("Do you still want to cancel this invitation?");
                    yesItem.setText(i18nc("@action:button", "Cancel Invitation"));
                }
                yesItem.setIconName(QStringLiteral("dialog-ok"));
                noItem.setText(i18nc("@action:button", "Do Not Cancel"));
                noItem.setIconName(QStringLiteral("dialog-cancel"));
            } else if (path == QLatin1StringView("check_calendar")) {
                queryStr = i18n("Do you still want to check your calendar?");
                yesItem.setText(i18nc("@action:button", "Check"));
            } else if (path == QLatin1StringView("record")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you still want to record this task in your calendar?");
                } else {
                    queryStr = i18n("Do you still want to record this invitation in your calendar?");
                }
                yesItem.setText(i18nc("@action:button", "Record"));
            } else if (path == QLatin1StringView("cancel")) {
                if (type == Incidence::TypeTodo) {
                    queryStr = i18n("Do you really want to cancel this task?");
                    yesItem.setText(i18nc("@action:button", "Cancel Task"));
                } else {
                    queryStr = i18n("Do you really want to cancel this invitation?");
                    yesItem.setText(i18nc("@action:button", "Cancel Invitation"));
                }
                yesItem.setIconName(QStringLiteral("dialog-ok"));
                noItem.setText(i18nc("@action:button", "Do Not Cancel"));
                noItem.setIconName(QStringLiteral("dialog-cancel"));
            } else if (path.startsWith(QLatin1StringView("ATTACH:"))) {
                return false;
            } else {
                queryStr = i18n("%1?", path);
                yesItem = KStandardGuiItem::ok();
            }

            if (noItem.text().isEmpty()) {
                noItem = KStandardGuiItem::cancel();
            }
            const int answer = KMessageBox::warningTwoActions(nullptr, i18n("%1\n%2", warnStr, queryStr), QString(), yesItem, noItem);
            if (answer == KMessageBox::ButtonCode::SecondaryAction) {
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
        qCDebug(TEXT_CALENDAR_LOG) << "Handling invitation: uid is : " << incidence->uid() << "; schedulingId is:" << incidence->schedulingID()
                                   << "; Attendee::PartStat = " << status;

        // get comment for tentative acceptance
        if (askForComment(status)) {
            QPointer<ReactionToInvitationDialog> dlg = new ReactionToInvitationDialog(nullptr);
            dlg->setWindowTitle(i18nc("@title:window", "Reaction to Invitation"));
            QString comment;
            if (dlg->exec()) {
                comment = dlg->comment();
                delete dlg;
            } else {
                delete dlg;
                return true;
            }

            if (comment.trimmed().isEmpty()) {
                KMessageBox::error(nullptr, i18n("You forgot to add proposal. Please add it. Thanks"));
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
                KMessageBox::error(nullptr, i18n("Delegation to organizer is not possible."));
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
            for (Attendee::List::ConstIterator it = attendees.constBegin(); it != end; ++it) {
                if (KEmailAddress::compareEmail((*it).fullName(), myself.delegator(), false) && (*it).status() == Attendee::Delegated) {
                    delegator = (*it).fullName();
                    delegatorRSVP = (*it).RSVP();
                    break;
                }
            }
        }

        if (status != Attendee::NeedsAction
            && ((!myself.isNull() && (myself.RSVP() || myself.status() == Attendee::NeedsAction)) || heuristicalRSVP(incidence))) {
            Attendee newMyself = setStatusOnMyself(incidence, myself, status, receiver);
            if (!newMyself.isNull() && status == Attendee::Delegated) {
                newMyself.setDelegate(delegateString);
                newMyself.setRSVP(delegatorRSVP);
            }
            ok = mail(viewerInstance, incidence, dir, iTIPReply, receiver);

            // check if we need to inform our delegator about this as well
            if (!newMyself.isNull() && (status == Attendee::Accepted || status == Attendee::Declined) && !delegator.isEmpty()) {
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
                Attendee newMyself(name,
                                   email,
                                   true, // RSVP, otherwise we would not be here
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
            QString name;
            QString email;
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

    void openAttachment(const QString &name, const QString &iCal) const
    {
        Attachment attachment(findAttachment(name, iCal));
        if (attachment.isEmpty()) {
            return;
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
                file = new QTemporaryFile(QDir::tempPath() + QLatin1StringView("/messageviewer_XXXXXX") + pattern.remove(QLatin1Char('*')));
            } else {
                file = new QTemporaryFile();
            }
            file->setAutoRemove(false);
            file->open();
            file->setPermissions(QFile::ReadUser);
            file->write(QByteArray::fromBase64(attachment.data()));
            file->close();

            auto job = new KIO::OpenUrlJob(QUrl::fromLocalFile(file->fileName()), attachment.mimeType());
            job->setDeleteTemporaryFile(true);
            job->start();
            delete file;
        }
    }

    [[nodiscard]] bool saveAsAttachment(const QString &name, const QString &iCal) const
    {
        Attachment a(findAttachment(name, iCal));
        if (a.isEmpty()) {
            return false;
        }

        // get the saveas file name
        const QString saveAsFile = QFileDialog::getSaveFileName(nullptr, i18nc("@title:window", "Save Invitation Attachment"), name, QString());

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
            QTemporaryFile *file{nullptr};
            QMimeDatabase db;
            QStringList patterns = db.mimeTypeForName(a.mimeType()).globPatterns();
            if (!patterns.empty()) {
                QString pattern = patterns.at(0);
                file = new QTemporaryFile(QDir::tempPath() + QLatin1StringView("/messageviewer_XXXXXX") + pattern.remove(QLatin1Char('*')));
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

    void showCalendar(QDate date) const
    {
        // Start or activate KOrganizer. When Kontact is running it will switch to KOrganizer view
        const auto korgaService = KService::serviceByDesktopName(QStringLiteral("org.kde.korganizer"));

        if (!korgaService) {
            qCWarning(TEXT_CALENDAR_LOG) << "Could not find KOrganizer";
            return;
        }

        auto job = new KIO::ApplicationLauncherJob(korgaService);
        QObject::connect(job, &KJob::finished, job, [date](KJob *job) {
            if (job->error()) {
                qCWarning(TEXT_CALENDAR_LOG) << "failed to run korganizer" << job->errorString();
                return;
            }

            OrgKdeKorganizerCalendarInterface iface(QStringLiteral("org.kde.korganizer"), QStringLiteral("/Calendar"), QDBusConnection::sessionBus(), nullptr);
            if (!iface.isValid()) {
                qCDebug(TEXT_CALENDAR_LOG) << "Calendar interface is not valid! " << iface.lastError().message();
                return;
            }
            iface.showEventView();
            iface.showDate(date);
        });

        job->start();
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
            dlg->setWindowTitle(i18nc("@title:window", "Decline Counter Proposal"));
            QString comment;
            if (dlg->exec()) {
                comment = dlg->comment();
                delete dlg;
            } else {
                delete dlg;
                return true;
            }

            if (comment.trimmed().isEmpty()) {
                KMessageBox::error(nullptr, i18n("You forgot to add proposal. Please add it. Thanks"));
                return true;
            } else {
                incidence->addComment(comment);
            }
        }
        return mail(viewerInstance, incidence, QStringLiteral("declinecounter"), KCalendarCore::iTIPDeclineCounter, receiver, QString(), DeclineCounter);
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
        if (path.contains(QLatin1StringView("addToAddressBook:")) || path.contains(QLatin1StringView("updateToAddressBook"))) {
            return false;
        }

        if (!hasMyWritableEventsFolders(QStringLiteral("calendar"))) {
            KMessageBox::error(nullptr,
                               i18n("You have no writable calendar folders for invitations, "
                                    "so storing or saving a response will not be possible.\n"
                                    "Please create at least 1 writable events calendar and re-sync."));
            return false;
        }

        // If the bodypart does not have a charset specified, we need to fall back to utf8,
        // not the KMail fallback encoding, so get the contents as binary and decode explicitly.
        QString iCal;
        if (!part->content()->contentType()->hasParameter("charset")) {
            const QByteArray &ba = part->content()->decodedContent();
            iCal = QString::fromUtf8(ba);
        } else {
            iCal = part->content()->decodedText();
        }

        Incidence::Ptr incidence = stringToIncidence(iCal);
        if (!incidence) {
            KMessageBox::error(nullptr,
                               i18n("The calendar invitation stored in this email message is broken in some way. "
                                    "Unable to continue."));
            return false;
        }

        bool result = false;
        if (cancelPastInvites(incidence, path)) {
            return result;
        }

        if (path == QLatin1StringView("accept")) {
            result = handleInvitation(iCal, Attendee::Accepted, part, viewerInstance);
        } else if (path == QLatin1StringView("accept_conditionally")) {
            result = handleInvitation(iCal, Attendee::Tentative, part, viewerInstance);
        } else if (path == QLatin1StringView("counter")) {
            result = counterProposal(iCal, part);
        } else if (path == QLatin1StringView("ignore")) {
            result = handleIgnore(viewerInstance);
        } else if (path == QLatin1StringView("decline")) {
            result = handleInvitation(iCal, Attendee::Declined, part, viewerInstance);
        } else if (path == QLatin1StringView("decline_counter")) {
            result = handleDeclineCounter(iCal, part, viewerInstance);
        } else if (path == QLatin1StringView("postpone")) {
            result = handleInvitation(iCal, Attendee::NeedsAction, part, viewerInstance);
        } else if (path == QLatin1StringView("delegate")) {
            result = handleInvitation(iCal, Attendee::Delegated, part, viewerInstance);
        } else if (path == QLatin1StringView("forward")) {
            AttendeeSelector dlg;
            if (dlg.exec() == QDialog::Rejected) {
                return true;
            }
            QString fwdTo = dlg.attendees().join(QLatin1StringView(", "));
            if (fwdTo.isEmpty()) {
                return true;
            }
            const QString receiver = findReceiver(part->content());
            result = mail(viewerInstance, incidence, QStringLiteral("forward"), iTIPRequest, receiver, fwdTo, Forward);
        } else if (path == QLatin1StringView("check_calendar")) {
            incidence = stringToIncidence(iCal);
            showCalendar(incidence->dtStart().date());
            return true;
        } else if (path == QLatin1StringView("reply") || path == QLatin1StringView("cancel") || path == QLatin1StringView("accept_counter")) {
            // These should just be saved with their type as the dir
            const QString p = (path == QLatin1StringView("accept_counter") ? QStringLiteral("reply") : path);
            if (saveFile(QStringLiteral("Receiver Not Searched"), iCal, p, part)) {
                if (MessageViewer::MessageViewerSettings::self()->deleteInvitationEmailsAfterSendingReply()) {
                    viewerInstance->deleteMessage();
                }
                result = true;
            }
        } else if (path == QLatin1StringView("record")) {
            incidence = stringToIncidence(iCal);
            QString summary;
            int response = KMessageBox::questionTwoActionsCancel(nullptr,
                                                                 i18nc("@info",
                                                                       "The organizer is not expecting a reply to this invitation "
                                                                       "but you can send them an email message if you desire.\n\n"
                                                                       "Would you like to send the organizer a message regarding this invitation?\n"
                                                                       "Press the [Cancel] button to cancel the recording operation."),
                                                                 i18nc("@title:window", "Send Email to Organizer"),
                                                                 KGuiItem(i18nc("@action:button", "Do Not Send")),
                                                                 KGuiItem(i18nc("@action:button", "Send EMail")));

            switch (response) {
            case KMessageBox::Cancel:
                break;
            case KMessageBox::ButtonCode::SecondaryAction: { // means "send email"
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
            // fall through
            case KMessageBox::ButtonCode::PrimaryAction: // means "do not send"
                if (saveFile(QStringLiteral("Receiver Not Searched"), iCal, QStringLiteral("reply"), part)) {
                    if (MessageViewer::MessageViewerSettings::self()->deleteInvitationEmailsAfterSendingReply()) {
                        viewerInstance->deleteMessage();
                        result = true;
                    }
                }
                showCalendar(incidence->dtStart().date());
                break;
            }
        } else if (path == QLatin1StringView("delete")) {
            viewerInstance->deleteMessage();
            result = true;
        }

        if (path.startsWith(QLatin1StringView("ATTACH:"))) {
            const QString name = QString::fromUtf8(QByteArray::fromBase64(path.mid(7).toUtf8()));
            openAttachment(name, iCal);
        }

        if (result) {
            // do not close the secondary window if an attachment was opened (kolab/issue4317)
            if (!path.startsWith(QLatin1StringView("ATTACH:"))) {
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
        if (path.startsWith(QLatin1StringView("ATTACH:"))) {
            name = QString::fromUtf8(QByteArray::fromBase64(path.mid(7).toUtf8()));
        } else {
            return false; // because it isn't an attachment invitation
        }

        QString iCal;
        if (!part->content()->contentType()->hasParameter("charset")) {
            const QByteArray &ba = part->content()->decodedContent();
            iCal = QString::fromUtf8(ba);
        } else {
            iCal = part->content()->decodedText();
        }

        auto menu = new QMenu();
        QAction *open = menu->addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("Open Attachment"));
        QAction *saveas = menu->addAction(QIcon::fromTheme(QStringLiteral("document-save-as")), i18n("Save Attachment As…"));

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
            if (path == QLatin1StringView("accept")) {
                return i18n("Accept invitation");
            } else if (path == QLatin1StringView("accept_conditionally")) {
                return i18n("Accept invitation conditionally");
            } else if (path == QLatin1StringView("accept_counter")) {
                return i18n("Accept counter proposal");
            } else if (path == QLatin1StringView("counter")) {
                return i18n("Create a counter proposal…");
            } else if (path == QLatin1StringView("ignore")) {
                return i18n("Throw mail away");
            } else if (path == QLatin1StringView("decline")) {
                return i18n("Decline invitation");
            } else if (path == QLatin1StringView("postpone")) {
                return i18n("Postpone");
            } else if (path == QLatin1StringView("decline_counter")) {
                return i18n("Decline counter proposal");
            } else if (path == QLatin1StringView("check_calendar")) {
                return i18n("Check my calendar…");
            } else if (path == QLatin1StringView("reply")) {
                return i18n("Record response into my calendar");
            } else if (path == QLatin1StringView("record")) {
                return i18n("Record invitation into my calendar");
            } else if (path == QLatin1StringView("delete")) {
                return i18n("Move this invitation to my trash folder");
            } else if (path == QLatin1StringView("delegate")) {
                return i18n("Delegate invitation");
            } else if (path == QLatin1StringView("forward")) {
                return i18n("Forward invitation");
            } else if (path == QLatin1StringView("cancel")) {
                return i18n("Remove invitation from my calendar");
            } else if (path.startsWith(QLatin1StringView("ATTACH:"))) {
                const QString name = QString::fromUtf8(QByteArray::fromBase64(path.mid(7).toUtf8()));
                return i18n("Open attachment \"%1\"", name);
            }
        }

        return {};
    }

    [[nodiscard]] bool askForComment(Attendee::PartStat status) const
    {
        if (status != Attendee::NeedsAction
            && ((status != Attendee::Accepted
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

    [[nodiscard]] const MessageViewer::Interface::BodyPartURLHandler *urlHandler(int idx) const override
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

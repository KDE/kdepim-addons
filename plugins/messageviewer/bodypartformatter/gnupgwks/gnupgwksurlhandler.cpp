/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "gnupgwksurlhandler.h"
#include "gnupgwks_debug.h"
#include "gnupgwksmessagepart.h"

#include <QProcess>
#include <QString>
#include <QUrlQuery>

#include <MessageViewer/Viewer>
#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/NodeHelper>

#include <QGpgME/Protocol>
#include <QGpgME/WKSPublishJob>

#include <Akonadi/MessageQueueJob>
#include <MailTransport/Transport>
#include <MailTransport/TransportManager>
#include <TextAddonsWidgets/ExecutableUtils>

#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/IdentityManager>

#include <KMime/Util>

#include <Akonadi/ItemDeleteJob>

#include <KLocalizedString>
using namespace Qt::Literals::StringLiterals;

using namespace MimeTreeParser::Interface;

bool ApplicationGnuPGWKSUrlHandler::handleContextMenuRequest(BodyPart *, const QString &, const QPoint &) const
{
    return false;
}

QString ApplicationGnuPGWKSUrlHandler::name() const
{
    return u"ApplicationGnuPGWKSUrlHandler"_s;
}

bool ApplicationGnuPGWKSUrlHandler::handleClick(MessageViewer::Viewer *viewerInstance, BodyPart *part, const QString &path) const
{
    Q_UNUSED(viewerInstance)

    if (!path.startsWith(QLatin1StringView("gnupgwks?"))) {
        return false;
    }

    const QUrlQuery q(path.mid(sizeof("gnupgwks?") - 1));
    if (q.queryItemValue(u"action"_s) == QLatin1StringView("show")) {
        const QString progFullPath = TextAddonsWidgets::ExecutableUtils::findExecutable(u"kleopatra"_s);
        if (progFullPath.isEmpty() || !QProcess::startDetached(u"kleopatra"_s, {u"--query"_s, q.queryItemValue(u"fpr"_s)})) {
            return false;
        }
        return true;
    } else if (q.queryItemValue(u"action"_s) == QLatin1StringView("confirm")) {
        GnuPGWKSMessagePart mp(part);
        if (!sendConfirmation(viewerInstance, mp)) {
            part->nodeHelper()->setProperty((u"__GnuPGWKS"_s + mp.fingerprint()).toLatin1().constData(), u"error"_s);
        }
        return true;
    }

    return false;
}

QString ApplicationGnuPGWKSUrlHandler::statusBarMessage(BodyPart *part, const QString &path) const
{
    Q_UNUSED(part)

    if (!path.startsWith(QLatin1StringView("gnupgwks?"))) {
        return {};
    }

    const QUrlQuery q(path.mid(sizeof("gnupgwks?") - 1));
    const QString actionStr = q.queryItemValue(u"action"_s);
    if (actionStr == QLatin1StringView("show")) {
        return i18n("Display key details");
    } else if (actionStr == QLatin1StringView("confirm")) {
        return i18n("Publish the key");
    }
    return {};
}

QByteArray ApplicationGnuPGWKSUrlHandler::createConfirmation(const std::shared_ptr<KMime::Message> &msg) const
{
    auto job = QGpgME::openpgp()->wksPublishJob();
    QEventLoop el;
    QByteArray result;
    QObject::connect(job,
                     &QGpgME::WKSPublishJob::result,
                     job,
                     [&el, &result](const GpgME::Error &, const QByteArray &returnedData, const QByteArray &returnedError) {
                         if (returnedData.isEmpty()) {
                             qCWarning(GNUPGWKS_LOG) << "GPG:" << returnedError;
                         }
                         result = returnedData;
                         el.quit();
                     });
    job->startReceive(msg->encodedContent());
    el.exec();

    return result;
}

bool ApplicationGnuPGWKSUrlHandler::sendConfirmation(MessageViewer::Viewer *viewerInstance, const GnuPGWKSMessagePart &mp) const
{
    const QByteArray data = createConfirmation(viewerInstance->message());
    if (data.isEmpty()) {
        return false;
    }

    auto msg = std::make_shared<KMime::Message>();
    msg->setContent(KMime::CRLFtoLF(data));
    msg->parse();

    // Find identity
    const auto identity = KIdentityManagementCore::IdentityManager::self()->identityForAddress(mp.address());
    const bool nullIdentity = (identity == KIdentityManagementCore::Identity::null());
    if (!nullIdentity) {
        auto x_header = std::unique_ptr<KMime::Headers::Generic>(new KMime::Headers::Generic("X-KMail-Identity"));
        x_header->from7BitString(QByteArray::number(identity.uoid()));
        msg->setHeader(std::move(x_header));
    }

    // Find transport set in the identity, fallback to default transport
    auto transportMgr = MailTransport::TransportManager::self();
    const bool identityHasTransport = !identity.transport().isEmpty();
    int transportId = -1;
    if (!nullIdentity && identityHasTransport) {
        transportId = identity.transport().toInt();
    } else {
        transportId = transportMgr->defaultTransportId();
    }
    // No transport exists, ask user to create one
    if (transportId == -1) {
        if (!transportMgr->showTransportCreationDialog(nullptr, MailTransport::TransportManager::IfNoTransportExists)) {
            return false;
        }
        transportId = transportMgr->defaultTransportId();
    }
    auto header = std::unique_ptr<KMime::Headers::Generic>(new KMime::Headers::Generic("X-KMail-Transport"));
    header->fromUnicodeString(QString::number(transportId));
    msg->setHeader(std::move(header));

    // Build the message
    msg->assemble();

    // Move to outbox
    auto transport = transportMgr->transportById(transportId);
    auto job = new Akonadi::MessageQueueJob;
    job->addressAttribute().setTo({msg->to(KMime::CreatePolicy::DontCreate)->asUnicodeString()});
    job->transportAttribute().setTransportId(transport->id());
    job->addressAttribute().setFrom(msg->from(KMime::CreatePolicy::DontCreate)->asUnicodeString());
    job->sentBehaviourAttribute().setSentBehaviour(Akonadi::SentBehaviourAttribute::Delete);
    job->sentBehaviourAttribute().setSendSilently(true);
    job->setMessage(msg);

    // Send
    if (!job->exec()) {
        qCWarning(GNUPGWKS_LOG) << "Error queuing message in output:" << job->errorText();
        return false;
    }

    // Delete the original request
    // Don't use viewerInstance->deleteMessage(), which triggers Move To Trash,
    // we want to get rid of the message for good.
    new Akonadi::ItemDeleteJob(viewerInstance->messageItem());
    return true;
}

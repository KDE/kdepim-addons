/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "operasettings.h"
#include "operaplugin_debug.h"
#include <MailImporter/FilterOpera>

#include <MailCommon/MailUtil>
#include <MailTransport/TransportManager>

#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/Signature>

#include <KConfig>
#include <KConfigGroup>
#include <QFile>
#include <QRegularExpression>

OperaSettings::OperaSettings(const QString &filename)
    : mFileName(filename)
{
}

void OperaSettings::importSettings()
{
    if (QFileInfo::exists(mFileName)) {
        KConfig config(mFileName);
        KConfigGroup grp = config.group(QStringLiteral("Accounts"));
        readGlobalAccount(grp);
        const QStringList accountList = config.groupList().filter(QRegularExpression(QStringLiteral("Account\\d+")));
        const QStringList::const_iterator end(accountList.constEnd());
        for (QStringList::const_iterator it = accountList.constBegin(); it != end; ++it) {
            KConfigGroup group = config.group(*it);
            readAccount(group);
            readTransport(group);
            readIdentity(group);
        }
    }
}

OperaSettings::~OperaSettings() = default;

void OperaSettings::readAccount(const KConfigGroup &grp)
{
    const QString incomingProtocol = grp.readEntry(QStringLiteral("Incoming Protocol"));
    const int port = grp.readEntry(QStringLiteral("Incoming Port"), -1);

    const QString serverName = grp.readEntry(QStringLiteral("Incoming Servername"));
    const QString userName = grp.readEntry(QStringLiteral("Incoming Username"));

    const int secure = grp.readEntry(QStringLiteral("Secure Connection In"), -1);

    const int pollInterval = grp.readEntry(QStringLiteral("Poll Interval"), -1);

    const int authMethod = grp.readEntry(QStringLiteral("Incoming Authentication Method"), -1);

    const QString name = grp.readEntry(QStringLiteral("Account Name"));

    const bool enableManualCheck = (grp.readEntry(QStringLiteral("Manual Check Enabled"), 0) == 1);

    // TODO
    const bool markAsSeen = (grp.readEntry(QStringLiteral("Mark Read If Seen"), 0) == 1);
    Q_UNUSED(markAsSeen)

    QMap<QString, QVariant> settings;
    if (incomingProtocol == QLatin1String("IMAP")) {
        settings.insert(QStringLiteral("ImapServer"), serverName);
        settings.insert(QStringLiteral("UserName"), userName);
        if (port != -1) {
            settings.insert(QStringLiteral("ImapPort"), port);
        }
        if (secure == 1) {
            settings.insert(QStringLiteral("Safety"), QStringLiteral("STARTTLS"));
        } else if (secure == 0) {
            settings.insert(QStringLiteral("Safety"), QStringLiteral("None"));
        }

        if (pollInterval == 0) {
            settings.insert(QStringLiteral("IntervalCheckEnabled"), false);
        } else {
            settings.insert(QStringLiteral("IntervalCheckEnabled"), true);
            settings.insert(QStringLiteral("IntervalCheckTime"), pollInterval);
        }

        const QString agentIdentifyName = LibImportWizard::AbstractBase::createResource(QStringLiteral("akonadi_imap_resource"), name, settings);
        addToManualCheck(agentIdentifyName, enableManualCheck);
        // We have not settings for it => same than manual check
        addCheckMailOnStartup(agentIdentifyName, enableManualCheck);
    } else if (incomingProtocol == QLatin1String("POP")) {
        settings.insert(QStringLiteral("Host"), serverName);
        settings.insert(QStringLiteral("Login"), userName);

        const int leaveOnServer = grp.readEntry(QStringLiteral("Leave On Server"), -1);
        if (leaveOnServer == 1) {
            settings.insert(QStringLiteral("LeaveOnServer"), true);
        } else if (leaveOnServer == 0) {
            settings.insert(QStringLiteral("LeaveOnServer"), false);
        } else {
            qCDebug(OPERAPLUGIN_LOG) << " leave on server option unknown : " << leaveOnServer;
        }

        const int removeMailFromSever = grp.readEntry(QStringLiteral("Remove From Server Delay Enabled"), -1);
        if (removeMailFromSever == 1) {
            int removeDelay = grp.readEntry(QStringLiteral("Remove From Server Delay"), -1);
            if (removeDelay != -1) {
                // Opera store delay as second !!! :)
                removeDelay = removeDelay / (24 * 60 * 60);
                settings.insert(QStringLiteral("LeaveOnServerDays"), removeDelay);
            }
        } // TODO: else

        if (port != -1) {
            settings.insert(QStringLiteral("Port"), port);
        }
        // TODO:
        const int delay = grp.readEntry(QStringLiteral("Initial Poll Delay"), -1);
        Q_UNUSED(delay)

        if (pollInterval == 0) {
            settings.insert(QStringLiteral("IntervalCheckEnabled"), false);
        } else {
            settings.insert(QStringLiteral("IntervalCheckEnabled"), true);
            settings.insert(QStringLiteral("IntervalCheckInterval"), pollInterval);
        }

        if (secure == 1) {
            settings.insert(QStringLiteral("UseTLS"), true);
        }

        switch (authMethod) {
        case 0: // NONE
            settings.insert(QStringLiteral("AuthenticationMethod"), MailTransport::Transport::EnumAuthenticationType::ANONYMOUS);
            break;
        case 1: // Clear Text
            settings.insert(QStringLiteral("AuthenticationMethod"), MailTransport::Transport::EnumAuthenticationType::CLEAR); // Verify
            break;
        case 6: // APOP
            settings.insert(QStringLiteral("AuthenticationMethod"), MailTransport::Transport::EnumAuthenticationType::APOP);
            break;
        case 10: // CRAM-MD5
            settings.insert(QStringLiteral("AuthenticationMethod"), MailTransport::Transport::EnumAuthenticationType::CRAM_MD5);
            break;
        case 31: // Automatic
            settings.insert(QStringLiteral("AuthenticationMethod"), MailTransport::Transport::EnumAuthenticationType::APOP); // TODO: verify
            break;
        default:
            qCDebug(OPERAPLUGIN_LOG) << " unknown authentication method :" << authMethod;
            break;
        }

        const QString agentIdentifyName = LibImportWizard::AbstractBase::createResource(QStringLiteral("akonadi_pop3_resource"), name, settings);
        // We have not settings for it => same than manual check
        addCheckMailOnStartup(agentIdentifyName, enableManualCheck);
        addToManualCheck(agentIdentifyName, enableManualCheck);
    } else {
        qCDebug(OPERAPLUGIN_LOG) << " protocol unknown : " << incomingProtocol;
    }
}

void OperaSettings::readTransport(const KConfigGroup &grp)
{
    const QString outgoingProtocol = grp.readEntry(QStringLiteral("Outgoing Protocol"));
    if (outgoingProtocol == QLatin1String("SMTP")) {
        const int authMethod = grp.readEntry(QStringLiteral("Outgoing Authentication Method"), -1);
        MailTransport::Transport *mt = createTransport();
        const int port = grp.readEntry(QStringLiteral("Outgoing Port"), -1);
        const int secure = grp.readEntry(QStringLiteral("Secure Connection Out"), -1);
        if (secure == 1) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::TLS);
        }
        if (port > 0) {
            mt->setPort(port);
        }

        const QString hostName = grp.readEntry(QStringLiteral("Outgoing Servername"));
        mt->setHost(hostName);

        const QString userName = grp.readEntry(QStringLiteral("Outgoing Username"));
        if (!userName.isEmpty()) {
            mt->setUserName(userName);
        }

        const int outgoingTimeOut = grp.readEntry(QStringLiteral("Outgoing Timeout"), -1); // TODO ?
        Q_UNUSED(outgoingTimeOut)

        switch (authMethod) {
        case 0: // NONE
            break;
        case 2: // PLAIN
            mt->setAuthenticationType(MailTransport::Transport::EnumAuthenticationType::PLAIN);
            break;
        case 5: // LOGIN
            mt->setAuthenticationType(MailTransport::Transport::EnumAuthenticationType::LOGIN);
            break;
        case 10: // CRAM-MD5
            mt->setAuthenticationType(MailTransport::Transport::EnumAuthenticationType::CRAM_MD5);
            break;
        case 31: // Automatic
            mt->setAuthenticationType(MailTransport::Transport::EnumAuthenticationType::PLAIN); // Don't know... Verify
            break;
        default:
            qCDebug(OPERAPLUGIN_LOG) << " authMethod unknown :" << authMethod;
        }

        // We can't specify a default smtp...
        storeTransport(mt, true);
    }
}

void OperaSettings::readIdentity(const KConfigGroup &grp)
{
    QString realName = grp.readEntry(QStringLiteral("Real Name"));
    KIdentityManagementCore::Identity *newIdentity = createIdentity(realName);
    const QString cc = grp.readEntry(QStringLiteral("Auto CC"));
    newIdentity->setCc(cc);

    const QString bcc = grp.readEntry(QStringLiteral("Auto BCC"));
    newIdentity->setBcc(bcc);

    const QString replyTo = grp.readEntry(QStringLiteral("Replyto"));
    if (!replyTo.isEmpty()) {
        newIdentity->setReplyToAddr(replyTo);
    }

    newIdentity->setFullName(realName);
    newIdentity->setIdentityName(realName);

    const QString email = grp.readEntry(QStringLiteral("Email"));
    newIdentity->setPrimaryEmailAddress(email);

    const QString organization = grp.readEntry(QStringLiteral("Organization"));
    if (!organization.isEmpty()) {
        newIdentity->setOrganization(organization);
    }

    QString signatureFile = grp.readEntry(QStringLiteral("Signature File"));
    if (!signatureFile.isEmpty()) {
        KIdentityManagementCore::Signature signature;
        const int signatureHtml = grp.readEntry(QStringLiteral("Signature is HTML"), -1);
        if (signatureFile.contains(QLatin1String("{Preferences}"))) {
            signatureFile.replace(QStringLiteral("{Preferences}"), MailImporter::FilterOpera::defaultSettingsPath() + QStringLiteral("/"));
        }

        QFile file(signatureFile);
        if (file.exists()) {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QByteArray sigText = file.readAll();

                switch (signatureHtml) {
                case -1:
                    break;
                case 0:
                    signature.setInlinedHtml(false);
                    signature.setType(KIdentityManagementCore::Signature::Inlined);
                    signature.setText(QString::fromUtf8(sigText));
                    break;
                case 1:
                    signature.setInlinedHtml(true);
                    signature.setType(KIdentityManagementCore::Signature::Inlined);
                    signature.setText(QString::fromUtf8(sigText));
                    break;
                default:
                    qCDebug(OPERAPLUGIN_LOG) << " pb with Signature is HTML " << signatureHtml;
                    break;
                }
                newIdentity->setSignature(signature);
            }
        }
    }
    storeIdentity(newIdentity);
}

void OperaSettings::readGlobalAccount(const KConfigGroup &grp)
{
    Q_UNUSED(grp)
    // TODO
}

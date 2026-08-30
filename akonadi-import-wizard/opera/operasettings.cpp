/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

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
using namespace Qt::Literals::StringLiterals;

OperaSettings::OperaSettings(const QString &filename)
    : mFileName(filename)
{
}

void OperaSettings::importSettings()
{
    if (QFileInfo::exists(mFileName)) {
        KConfig config(mFileName);
        KConfigGroup grp = config.group(u"Accounts"_s);
        readGlobalAccount(grp);
        const QStringList accountList = config.groupList().filter(QRegularExpression(u"Account\\d+"_s));
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
    const QString incomingProtocol = grp.readEntry(u"Incoming Protocol"_s);
    const int port = grp.readEntry(u"Incoming Port"_s, -1);

    const QString serverName = grp.readEntry(u"Incoming Servername"_s);
    const QString userName = grp.readEntry(u"Incoming Username"_s);

    const int secure = grp.readEntry(u"Secure Connection In"_s, -1);

    const int pollInterval = grp.readEntry(u"Poll Interval"_s, -1);

    const int authMethod = grp.readEntry(u"Incoming Authentication Method"_s, -1);

    const QString name = grp.readEntry(u"Account Name"_s);

    const bool enableManualCheck = (grp.readEntry(u"Manual Check Enabled"_s, 0) == 1);

    // TODO
    const bool markAsSeen = (grp.readEntry(u"Mark Read If Seen"_s, 0) == 1);
    Q_UNUSED(markAsSeen)

    QMap<QString, QVariant> settings;
    if (incomingProtocol == "IMAP"_L1) {
        settings.insert(u"ImapServer"_s, serverName);
        settings.insert(u"UserName"_s, userName);
        if (port != -1) {
            settings.insert(u"ImapPort"_s, port);
        }
        if (secure == 1) {
            settings.insert(u"Safety"_s, u"STARTTLS"_s);
        } else if (secure == 0) {
            settings.insert(u"Safety"_s, u"None"_s);
        }

        if (pollInterval == 0) {
            settings.insert(u"IntervalCheckEnabled"_s, false);
        } else {
            settings.insert(u"IntervalCheckEnabled"_s, true);
            settings.insert(u"IntervalCheckTime"_s, pollInterval);
        }

        const QString agentIdentifyName = LibImportWizard::AbstractBase::createResource(u"akonadi_imap_resource"_s, name, settings);
        addToManualCheck(agentIdentifyName, enableManualCheck);
        // We have not settings for it => same than manual check
        addCheckMailOnStartup(agentIdentifyName, enableManualCheck);
    } else if (incomingProtocol == "POP"_L1) {
        settings.insert(u"Host"_s, serverName);
        settings.insert(u"Login"_s, userName);

        const int leaveOnServer = grp.readEntry(u"Leave On Server"_s, -1);
        if (leaveOnServer == 1) {
            settings.insert(u"LeaveOnServer"_s, true);
        } else if (leaveOnServer == 0) {
            settings.insert(u"LeaveOnServer"_s, false);
        } else {
            qCDebug(OPERAPLUGIN_LOG) << " leave on server option unknown : " << leaveOnServer;
        }

        const int removeMailFromSever = grp.readEntry(u"Remove From Server Delay Enabled"_s, -1);
        if (removeMailFromSever == 1) {
            int removeDelay = grp.readEntry(u"Remove From Server Delay"_s, -1);
            if (removeDelay != -1) {
                // Opera store delay as second !!! :)
                removeDelay = removeDelay / (24 * 60 * 60);
                settings.insert(u"LeaveOnServerDays"_s, removeDelay);
            }
        } // TODO: else

        if (port != -1) {
            settings.insert(u"Port"_s, port);
        }
        // TODO:
        const int delay = grp.readEntry(u"Initial Poll Delay"_s, -1);
        Q_UNUSED(delay)

        if (pollInterval == 0) {
            settings.insert(u"IntervalCheckEnabled"_s, false);
        } else {
            settings.insert(u"IntervalCheckEnabled"_s, true);
            settings.insert(u"IntervalCheckInterval"_s, pollInterval);
        }

        if (secure == 1) {
            settings.insert(u"UseTLS"_s, true);
        }

        switch (authMethod) {
        case 0: // NONE
            settings.insert(u"AuthenticationMethod"_s, MailTransport::Transport::EnumAuthenticationType::ANONYMOUS);
            break;
        case 1: // Clear Text
            settings.insert(u"AuthenticationMethod"_s, MailTransport::Transport::EnumAuthenticationType::CLEAR); // Verify
            break;
        case 6: // APOP
            settings.insert(u"AuthenticationMethod"_s, MailTransport::Transport::EnumAuthenticationType::APOP);
            break;
        case 10: // CRAM-MD5
            settings.insert(u"AuthenticationMethod"_s, MailTransport::Transport::EnumAuthenticationType::CRAM_MD5);
            break;
        case 31: // Automatic
            settings.insert(u"AuthenticationMethod"_s, MailTransport::Transport::EnumAuthenticationType::APOP); // TODO: verify
            break;
        default:
            qCDebug(OPERAPLUGIN_LOG) << " unknown authentication method :" << authMethod;
            break;
        }

        const QString agentIdentifyName = LibImportWizard::AbstractBase::createResource(u"akonadi_pop3_resource"_s, name, settings);
        // We have not settings for it => same than manual check
        addCheckMailOnStartup(agentIdentifyName, enableManualCheck);
        addToManualCheck(agentIdentifyName, enableManualCheck);
    } else {
        qCDebug(OPERAPLUGIN_LOG) << " protocol unknown : " << incomingProtocol;
    }
}

void OperaSettings::readTransport(const KConfigGroup &grp)
{
    const QString outgoingProtocol = grp.readEntry(u"Outgoing Protocol"_s);
    if (outgoingProtocol == "SMTP"_L1) {
        const int authMethod = grp.readEntry(u"Outgoing Authentication Method"_s, -1);
        MailTransport::Transport *mt = createTransport();
        const int port = grp.readEntry(u"Outgoing Port"_s, -1);
        const int secure = grp.readEntry(u"Secure Connection Out"_s, -1);
        if (secure == 1) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::TLS);
        }
        if (port > 0) {
            mt->setPort(port);
        }

        const QString hostName = grp.readEntry(u"Outgoing Servername"_s);
        mt->setHost(hostName);

        const QString userName = grp.readEntry(u"Outgoing Username"_s);
        if (!userName.isEmpty()) {
            mt->setUserName(userName);
        }

        const int outgoingTimeOut = grp.readEntry(u"Outgoing Timeout"_s, -1); // TODO ?
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
    QString realName = grp.readEntry(u"Real Name"_s);
    KIdentityManagementCore::Identity *newIdentity = createIdentity(realName);
    const QString cc = grp.readEntry(u"Auto CC"_s);
    newIdentity->setCc(cc);

    const QString bcc = grp.readEntry(u"Auto BCC"_s);
    newIdentity->setBcc(bcc);

    const QString replyTo = grp.readEntry(u"Replyto"_s);
    if (!replyTo.isEmpty()) {
        newIdentity->setReplyToAddr(replyTo);
    }

    newIdentity->setFullName(realName);
    newIdentity->setIdentityName(realName);

    const QString email = grp.readEntry(u"Email"_s);
    newIdentity->setPrimaryEmailAddress(email);

    const QString organization = grp.readEntry(u"Organization"_s);
    if (!organization.isEmpty()) {
        newIdentity->setOrganization(organization);
    }

    QString signatureFile = grp.readEntry(u"Signature File"_s);
    if (!signatureFile.isEmpty()) {
        KIdentityManagementCore::Signature signature;
        const int signatureHtml = grp.readEntry(u"Signature is HTML"_s, -1);
        if (signatureFile.contains("{Preferences}"_L1)) {
            signatureFile.replace(u"{Preferences}"_s, MailImporter::FilterOpera::defaultSettingsPath() + u"/"_s);
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

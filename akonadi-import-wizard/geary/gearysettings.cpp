/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "gearysettings.h"
#include <ImportWizard/ImportWizardUtil>

#include <mailtransport/transportmanager.h>

#include <KIdentityManagement/kidentitymanagement/identity.h>
#include <KIdentityManagement/kidentitymanagement/signature.h>

#include <QSettings>

GearySettings::GearySettings(const QString &filename)
{
    settings = new QSettings(filename, QSettings::IniFormat, this);
}

GearySettings::~GearySettings()
{
    delete settings;
}

void GearySettings::importSettings()
{
    readImapAccount();
    readTransport();
    readIdentity();
    readGlobalSettings();
}

void GearySettings::readImapAccount()
{
    QMap<QString, QVariant> newSettings;

    QString name;

    name = settings->value(QStringLiteral("imap_host")).toString();
    if (!name.isEmpty()) {
        newSettings.insert(QStringLiteral("ImapServer"), name);
    }
#if 0
    imap_host=hostname
    imap_port=143
    imap_ssl=false
    imap_starttls=true
    imap_username=username
#endif

    const QString username = settings->value(QStringLiteral("imap_username")).toString();
    newSettings.insert(QStringLiteral("UserName"), username);

    const int port = settings->value(QStringLiteral("imap_port"), -1).toInt();
    if (port > -1) {
        newSettings.insert(QStringLiteral("ImapPort"), port);
    }

    if (settings->contains(QStringLiteral("imap_starttls"))) {
        const bool useTLS = settings->value(QStringLiteral("imap_starttls")).toBool();
        if (useTLS) {
            newSettings.insert(QStringLiteral("Safety"), QStringLiteral("STARTTLS"));
        }
    }
    if (settings->contains(QStringLiteral("imap_ssl"))) {
        const bool useSSL = settings->value(QStringLiteral("imap_ssl")).toBool();
        if (useSSL) {
            newSettings.insert(QStringLiteral("Safety"), QStringLiteral("SSL"));
        }
    }

    if (!name.isEmpty()) {
        const QString agentIdentifyName = LibImportWizard::AbstractBase::createResource(QStringLiteral("akonadi_imap_resource"), name, newSettings);
        //Check by default
        addCheckMailOnStartup(agentIdentifyName, true);
    }
}

void GearySettings::readTransport()
{
    const QString host = settings->value(QStringLiteral("smtp_host")).toString();
    if (!host.isEmpty()) {
        MailTransport::Transport *mt = createTransport();
        mt->setIdentifier(QStringLiteral("SMTP"));
        mt->setHost(host);
        const int port = settings->value(QStringLiteral("smtp_port"), -1).toInt();
        if (port != -1) {
            mt->setPort(port);
        }

        if (!settings->value(QStringLiteral("smtp_noauth"), true).toBool()) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::None);
        }
        if (settings->value(QStringLiteral("smtp_ssl"), true).toBool()) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::SSL);
        }
        if (settings->value(QStringLiteral("smtp_starttls"), true).toBool()) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::TLS);
        }

        //ADD more settings
        storeTransport(mt, true);   //only one smtp for the moment
    }
#if 0
    smtp_host = smtp.bla.bla
            smtp_port = 465
            smtp_ssl = true
            smtp_starttls = false
            smtp_use_imap_credentials = false
            smtp_noauth = true
#endif
#if 0
    const QString smtpMethod = settings->value(QStringLiteral("msa.method")).toString();
    if (!smtpMethod.isEmpty()) {
        MailTransport::Transport *mt = createTransport();
        if (smtpMethod == QLatin1String("IMAP-SENDMAIL")) {
            //see http://tools.ietf.org/html/draft-kundrat-imap-submit-01
        } else if (smtpMethod == QLatin1String("SMTP") || smtpMethod == QLatin1String("SSMTP")) {
            if (settings->contains(QStringLiteral("msa.smtp.host"))) {
                mt->setHost(settings->value(QStringLiteral("msa.smtp.host")).toString());
            }
            if (settings->contains(QStringLiteral("msa.smtp.port"))) {
                mt->setPort(settings->value(QStringLiteral("msa.smtp.port")).toInt());
            }
            if (settings->contains(QStringLiteral("msa.smtp.auth"))) {
                if (settings->value(QStringLiteral("msa.smtp.auth")).toBool()) {
                    if (settings->contains(QStringLiteral("msa.smtp.auth.user"))) {
                        mt->setUserName(settings->value(QStringLiteral("msa.smtp.auth.user")).toString());
                    }
                    if (settings->contains(QStringLiteral("msa.smtp.auth.pass"))) {
                        mt->setPassword(settings->value(QStringLiteral("msa.smtp.auth.pass")).toString());
                    }
                }
            }

            if (settings->contains(QStringLiteral("msa.smtp.starttls"))) {
                if (settings->value(QStringLiteral("msa.smtp.starttls")).toBool()) {
                    mt->setEncryption(MailTransport::Transport::EnumEncryption::TLS);
                }
            }
            mt->setType(MailTransport::Transport::EnumType::SMTP);
        } else {
            qCWarning(IMPORTWIZARD_LOG) << " smtpMethod unknown " << smtpMethod;
        }
        storeTransport(mt, true);   //only one smtp for the moment
    }
#endif
}

void GearySettings::readIdentity()
{
    QString realName = settings->value(QStringLiteral("realName")).toString();
    if (!realName.isEmpty()) {
        KIdentityManagement::Identity *identity = createIdentity(realName);
        identity->setFullName(realName);
        identity->setIdentityName(realName);
        const QString address = settings->value(QStringLiteral("primary_email")).toString();
        identity->setPrimaryEmailAddress(address);
        const QString alias = settings->value(QStringLiteral("alternate_emails")).toString();
        if (!alias.isEmpty()) {
            identity->setEmailAliases(alias.split(QLatin1Char(';'), QString::SkipEmptyParts));
        }
        const QString signatureStr = settings->value(QStringLiteral("email_signature")).toString();
        if (!signatureStr.isEmpty()) {
            KIdentityManagement::Signature signature;
            signature.setType(KIdentityManagement::Signature::Inlined);
            signature.setText(signatureStr);
            const bool useSignature = settings->value(QStringLiteral("use_email_signature"), true).toBool();
            signature.setEnabledSignature(useSignature);
            identity->setSignature(signature);
        }

        //TODO add "nickname=bli@kde.org"
        storeIdentity(identity);
    }
}

void GearySettings::readGlobalSettings()
{
    //TODO
}

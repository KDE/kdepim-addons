/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

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

    QString name = settings->value(QStringLiteral("imap_host")).toString();
    if (!name.isEmpty()) {
        newSettings.insert(QStringLiteral("ImapServer"), name);
    }

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
        } else if (settings->value(QStringLiteral("smtp_ssl"), true).toBool()) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::SSL);
        } else if (settings->value(QStringLiteral("smtp_starttls"), true).toBool()) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::TLS);
        }

        if (settings->value(QStringLiteral("smtp_use_imap_credentials"), true).toBool()) {
            //TODO store value
        }

        //ADD more settings
        storeTransport(mt, true);   //only one smtp for the moment
    }
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

        //Implement  "nickname=bli@kde.org" ?
        storeIdentity(identity);
    }
}

void GearySettings::readGlobalSettings()
{
    //TODO
}

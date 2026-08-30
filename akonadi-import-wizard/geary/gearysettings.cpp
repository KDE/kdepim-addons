/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gearysettings.h"
#include <ImportWizard/ImportWizardUtil>

#include <MailTransport/TransportManager>

#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/Signature>

#include <QSettings>
using namespace Qt::Literals::StringLiterals;

GearySettings::GearySettings(const QString &filename)
    : settings(new QSettings(filename, QSettings::IniFormat, this))
{
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

    QString name = settings->value(u"imap_host"_s).toString();
    if (!name.isEmpty()) {
        newSettings.insert(u"ImapServer"_s, name);
    }

    const QString username = settings->value(u"imap_username"_s).toString();
    newSettings.insert(u"UserName"_s, username);

    const int port = settings->value(u"imap_port"_s, -1).toInt();
    if (port > -1) {
        newSettings.insert(u"ImapPort"_s, port);
    }

    if (settings->contains(u"imap_starttls"_s)) {
        const bool useTLS = settings->value(u"imap_starttls"_s).toBool();
        if (useTLS) {
            newSettings.insert(u"Safety"_s, u"STARTTLS"_s);
        }
    }
    if (settings->contains(u"imap_ssl"_s)) {
        const bool useSSL = settings->value(u"imap_ssl"_s).toBool();
        if (useSSL) {
            newSettings.insert(u"Safety"_s, u"SSL"_s);
        }
    }

    if (!name.isEmpty()) {
        const QString agentIdentifyName = LibImportWizard::AbstractBase::createResource(u"akonadi_imap_resource"_s, name, newSettings);
        // Check by default
        addCheckMailOnStartup(agentIdentifyName, true);
    }
}

void GearySettings::readTransport()
{
    const QString host = settings->value(u"smtp_host"_s).toString();
    if (!host.isEmpty()) {
        MailTransport::Transport *mt = createTransport();
        mt->setIdentifier(u"SMTP"_s);
        mt->setHost(host);
        const int port = settings->value(u"smtp_port"_s, -1).toInt();
        if (port != -1) {
            mt->setPort(port);
        }

        if (!settings->value(u"smtp_noauth"_s, true).toBool()) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::None);
        } else if (settings->value(u"smtp_ssl"_s, true).toBool()) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::SSL);
        } else if (settings->value(u"smtp_starttls"_s, true).toBool()) {
            mt->setEncryption(MailTransport::Transport::EnumEncryption::TLS);
        }

        if (settings->value(u"smtp_use_imap_credentials"_s, true).toBool()) {
            // TODO store value
        }

        // ADD more settings
        storeTransport(mt, true); // only one smtp for the moment
    }
}

void GearySettings::readIdentity()
{
    QString realName = settings->value(u"realName"_s).toString();
    if (!realName.isEmpty()) {
        KIdentityManagementCore::Identity *identity = createIdentity(realName);
        identity->setFullName(realName);
        identity->setIdentityName(realName);
        const QString address = settings->value(u"primary_email"_s).toString();
        identity->setPrimaryEmailAddress(address);
        const QString alias = settings->value(u"alternate_emails"_s).toString();
        if (!alias.isEmpty()) {
            identity->setEmailAliases(alias.split(QLatin1Char(';'), Qt::SkipEmptyParts));
        }
        const QString signatureStr = settings->value(u"email_signature"_s).toString();
        if (!signatureStr.isEmpty()) {
            KIdentityManagementCore::Signature signature;
            signature.setType(KIdentityManagementCore::Signature::Inlined);
            signature.setText(signatureStr);
            const bool useSignature = settings->value(u"use_email_signature"_s, true).toBool();
            signature.setEnabledSignature(useSignature);
            identity->setSignature(signature);
        }

        // Implement  "nickname=bli@kde.org" ?
        storeIdentity(identity);
    }
}

void GearySettings::readGlobalSettings()
{
    // TODO
}

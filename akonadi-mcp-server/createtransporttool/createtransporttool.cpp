/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createtransporttool.h"
#include "common/toolutils.h"
#include <KLocalizedString>
#include <MailTransport/Transport>
#include <MailTransport/TransportManager>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;

namespace
{
const QString encryptionNone = u"none"_s;
const QString encryptionSsl = u"ssl"_s;
const QString encryptionTls = u"starttls"_s;

struct AuthenticationTypeInfo {
    QString name;
    MailTransport::Transport::EnumAuthenticationType type;
};

const QList<AuthenticationTypeInfo> &authenticationTypes()
{
    static const QList<AuthenticationTypeInfo> types{
        {u"login"_s, MailTransport::Transport::EnumAuthenticationType::LOGIN},
        {u"plain"_s, MailTransport::Transport::EnumAuthenticationType::PLAIN},
        {u"cram-md5"_s, MailTransport::Transport::EnumAuthenticationType::CRAM_MD5},
        {u"digest-md5"_s, MailTransport::Transport::EnumAuthenticationType::DIGEST_MD5},
        {u"gssapi"_s, MailTransport::Transport::EnumAuthenticationType::GSSAPI},
        {u"ntlm"_s, MailTransport::Transport::EnumAuthenticationType::NTLM},
    };
    return types;
}

QStringList authenticationTypeNames()
{
    QStringList names;
    for (const auto &info : authenticationTypes()) {
        names.append(info.name);
    }
    return names;
}
}

CreateTransportTool::CreateTransportTool() = default;
CreateTransportTool::~CreateTransportTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CreateTransportTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_create_transport"_s,
        i18n("Create Mail Transport"),
        u"Create a new SMTP mail transport (outgoing mail server account)"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::Modify,
        QMap<QString, QJsonObject>{
            {u"name"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Name of the transport. If omitted, the host is used"_s)},
            {u"host"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Host name of the SMTP server"_s)},
            {u"port"_s,
             McpProtocolServerTool::schemaProperty(u"integer"_s, u"Port of the SMTP server. If omitted, 465 for ssl, 587 for starttls and 25 otherwise"_s)},
            {u"encryption"_s,
             McpProtocolServerTool::schemaEnumProperty({encryptionNone, encryptionSsl, encryptionTls}, u"Encryption used by the connection (default ssl)"_s)},
            {u"user_name"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"User name used to authenticate. If omitted, no authentication is used"_s)},
            {u"password"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Password used to authenticate, stored in the wallet"_s)},
            {u"authentication_type"_s,
             McpProtocolServerTool::schemaEnumProperty(authenticationTypeNames(), u"Authentication method, used only with user_name (default plain)"_s)},
            {u"set_as_default"_s, McpProtocolServerTool::schemaProperty(u"boolean"_s, u"Make this transport the default one (default false)"_s)}},
        {u"host"_s});
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
    return tool;
}

void CreateTransportTool::doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString host = arguments.value(u"host"_s).toString().trimmed();
    if (host.isEmpty()) {
        call->finishWithText(i18n("Argument host must be a non-empty string"), true);
        return;
    }

    MailTransport::Transport::EnumEncryption encryption = MailTransport::Transport::EnumEncryption::SSL;
    const QString encryptionStr = arguments.value(u"encryption"_s).toString().trimmed().toLower();
    if (encryptionStr == encryptionNone) {
        encryption = MailTransport::Transport::EnumEncryption::None;
    } else if (encryptionStr == encryptionTls) {
        encryption = MailTransport::Transport::EnumEncryption::TLS;
    } else if (!encryptionStr.isEmpty() && encryptionStr != encryptionSsl) {
        call->finishWithText(i18n("Invalid encryption \"%1\", expected none, ssl or starttls", encryptionStr), true);
        return;
    }

    int port = 25;
    if (encryption == MailTransport::Transport::EnumEncryption::SSL) {
        port = 465;
    } else if (encryption == MailTransport::Transport::EnumEncryption::TLS) {
        port = 587;
    }
    const QJsonValue portValue = arguments.value(u"port"_s);
    if (const std::optional<qint64> portInteger = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::integer(portValue)) {
        if (*portInteger <= 0 || *portInteger > 65535) {
            call->finishWithText(i18n("Argument port must be between 1 and 65535"), true);
            return;
        }
        port = static_cast<int>(*portInteger);
    } else if (TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(portValue)) {
        call->finishWithText(i18n("Argument port must be an integer"), true);
        return;
    }

    MailTransport::Transport::EnumAuthenticationType authenticationType = MailTransport::Transport::EnumAuthenticationType::PLAIN;
    if (const QString authenticationStr = arguments.value(u"authentication_type"_s).toString().trimmed().toLower(); !authenticationStr.isEmpty()) {
        const auto &types = authenticationTypes();
        const auto it = std::find_if(types.cbegin(), types.cend(), [&authenticationStr](const AuthenticationTypeInfo &info) {
            return info.name == authenticationStr;
        });
        if (it == types.cend()) {
            call->finishWithText(i18n("Invalid authentication_type \"%1\", expected one of: %2", authenticationStr, authenticationTypeNames().join(u", "_s)),
                                 true);
            return;
        }
        authenticationType = it->type;
    }

    bool setAsDefault = false;
    const QJsonValue defaultValue = arguments.value(u"set_as_default"_s);
    if (const std::optional<bool> defaultBool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::boolean(defaultValue)) {
        setAsDefault = *defaultBool;
    } else if (TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(defaultValue)) {
        call->finishWithText(i18n("Argument set_as_default must be a boolean"), true);
        return;
    }

    QString name = arguments.value(u"name"_s).toString().trimmed();
    if (name.isEmpty()) {
        name = host;
    }
    const QString userName = arguments.value(u"user_name"_s).toString().trimmed();
    const QString password = arguments.value(u"password"_s).toString();

    auto manager = MailTransport::TransportManager::self();
    MailTransport::Transport *transport = manager->createTransport();
    transport->setIdentifier(u"SMTP"_s);
    transport->setName(name);
    transport->setHost(host);
    transport->setPort(port);
    transport->setEncryption(encryption);
    if (!userName.isEmpty()) {
        transport->setRequiresAuthentication(true);
        transport->setUserName(userName);
        transport->setAuthenticationType(authenticationType);
        if (!password.isEmpty()) {
            transport->setStorePassword(true);
            transport->setPassword(password);
        }
    }
    transport->forceUniqueName();
    transport->save();
    manager->addTransport(transport);
    if (setAsDefault) {
        manager->setDefaultTransport(transport->id());
    }

    call->finishWithText(i18n("Transport \"%1\" created (id %2)", transport->name(), transport->id()));
}

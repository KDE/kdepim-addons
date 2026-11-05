/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createidentitytool.h"
#include "common/toolutils.h"
#include <KEmailAddress>
#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/IdentityManager>
#include <KIdentityManagementCore/Signature>
#include <KLocalizedString>
#include <MailTransport/TransportManager>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;

CreateIdentityTool::CreateIdentityTool() = default;
CreateIdentityTool::~CreateIdentityTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CreateIdentityTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"mail_create_identity"_s,
        i18n("Create Identity"),
        u"Create a new mail identity"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::Modify,
        QMap<QString, QJsonObject>{
            {u"email"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Primary email address of the identity"_s)},
            {u"full_name"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Full name of the sender"_s)},
            {u"identity_name"_s,
             McpProtocolServerTool::schemaProperty(u"string"_s, u"Name of the identity, made unique if needed. If omitted, the email address is used"_s)},
            {u"organization"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Organization"_s)},
            {u"email_aliases"_s, McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}), u"Email aliases"_s)},
            {u"reply_to"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Reply-To address"_s)},
            {u"cc"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Address always added as Cc"_s)},
            {u"bcc"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Address always added as Bcc"_s)},
            {u"signature"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Plain text signature"_s)},
            {u"transport_id"_s,
             McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the mail transport used to send mails (see mail_create_transport)"_s)},
            {u"set_as_default"_s, McpProtocolServerTool::schemaProperty(u"boolean"_s, u"Make this identity the default one (default false)"_s)}},
        {u"email"_s});
    ToolUtils::addToolMeta(tool, ToolUtils::Mail);
    return tool;
}

void CreateIdentityTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString email = arguments.value(u"email"_s).toString().trimmed();
    if (email.isEmpty()) {
        call->finishWithText(i18n("Argument email must be a non-empty string"), true);
        return;
    }
    if (!KEmailAddress::isValidSimpleAddress(email)) {
        call->finishWithText(i18n("Invalid email address \"%1\"", email), true);
        return;
    }

    QStringList aliases;
    if (!TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::readStringList(arguments.value(u"email_aliases"_s), aliases)) {
        call->finishWithText(i18n("Argument email_aliases must be an array of strings"), true);
        return;
    }
    for (const QString &alias : std::as_const(aliases)) {
        if (!KEmailAddress::isValidSimpleAddress(alias)) {
            call->finishWithText(i18n("Invalid email alias \"%1\"", alias), true);
            return;
        }
    }

    QString transportId;
    const QJsonValue transportValue = arguments.value(u"transport_id"_s);
    if (const std::optional<qint64> transportInteger = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::integer(transportValue)) {
        if (!MailTransport::TransportManager::self()->transportById(static_cast<int>(*transportInteger), false)) {
            call->finishWithText(i18n("No mail transport found with id %1", *transportInteger), true);
            return;
        }
        transportId = QString::number(*transportInteger);
    } else if (TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(transportValue)) {
        call->finishWithText(i18n("Argument transport_id must be an integer"), true);
        return;
    }

    bool setAsDefault = false;
    const QJsonValue defaultValue = arguments.value(u"set_as_default"_s);
    if (const std::optional<bool> defaultBool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::boolean(defaultValue)) {
        setAsDefault = *defaultBool;
    } else if (TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(defaultValue)) {
        call->finishWithText(i18n("Argument set_as_default must be a boolean"), true);
        return;
    }

    QString identityName = arguments.value(u"identity_name"_s).toString().trimmed();
    if (identityName.isEmpty()) {
        identityName = email;
    }

    auto manager = KIdentityManagementCore::IdentityManager::self();
    KIdentityManagementCore::Identity &identity = manager->newFromScratch(manager->makeUnique(identityName));
    identity.setPrimaryEmailAddress(email);
    identity.setEmailAliases(aliases);
    if (const QString fullName = arguments.value(u"full_name"_s).toString().trimmed(); !fullName.isEmpty()) {
        identity.setFullName(fullName);
    }
    if (const QString organization = arguments.value(u"organization"_s).toString().trimmed(); !organization.isEmpty()) {
        identity.setOrganization(organization);
    }
    if (const QString replyTo = arguments.value(u"reply_to"_s).toString().trimmed(); !replyTo.isEmpty()) {
        identity.setReplyToAddr(replyTo);
    }
    if (const QString cc = arguments.value(u"cc"_s).toString().trimmed(); !cc.isEmpty()) {
        identity.setCc(cc);
    }
    if (const QString bcc = arguments.value(u"bcc"_s).toString().trimmed(); !bcc.isEmpty()) {
        identity.setBcc(bcc);
    }
    if (const QString signatureText = arguments.value(u"signature"_s).toString(); !signatureText.trimmed().isEmpty()) {
        KIdentityManagementCore::Signature signature(signatureText);
        signature.setEnabledSignature(true);
        identity.setSignature(signature);
    }
    if (!transportId.isEmpty()) {
        identity.setTransport(transportId);
    }
    const uint uoid = identity.uoid();
    const QString finalName = identity.identityName();
    if (setAsDefault) {
        manager->setAsDefault(uoid);
    }
    manager->commit();

    call->finishWithText(i18n("Identity \"%1\" created (uoid %2)", finalName, uoid));
}

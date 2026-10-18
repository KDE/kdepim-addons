/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "updatecontacttool.h"
#include "common/toolutils.h"
#include <KLocalizedString>
#include <QDate>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

UpdateContactTool::UpdateContactTool() = default;
UpdateContactTool::~UpdateContactTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool UpdateContactTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_update"_s,
        u"Update an existing contact in an Akonadi address book. Only the provided fields are modified"_s,
        QMap<QString, QJsonObject>{
            {u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the contact item (see contact_search)"_s)},
            {u"name"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Full name of the contact"_s)},
            {u"emails"_s,
             McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}),
                                                        u"Email addresses, the first one is the preferred one. Replaces the existing ones"_s)},
            {u"phone_numbers"_s,
             McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}),
                                                        u"Phone numbers. Replaces the existing ones"_s)},
            {u"organization"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Organization of the contact"_s)},
            {u"birthday"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Birthday in ISO format (YYYY-MM-DD)"_s)},
            {u"note"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Free text note"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(true);
    annotation.setIdempotentHint(true);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("Update Contact"));
    tool.setAnnotations(annotation);
    return tool;
}

void UpdateContactTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QJsonValue idValue = arguments.value(u"id"_s);
    if (!idValue.isDouble()) {
        call->finishWithText(i18n("Argument id must be an integer"), true);
        return;
    }
    const qint64 itemId = idValue.toInteger(-1);
    if (itemId < 0) {
        call->finishWithText(i18n("Argument id must be a positive integer"), true);
        return;
    }

    QStringList emails;
    if (!ToolUtils::readStringList(arguments.value(u"emails"_s), emails)) {
        call->finishWithText(i18n("Argument emails must be an array of strings"), true);
        return;
    }

    QStringList phoneNumbers;
    if (!ToolUtils::readStringList(arguments.value(u"phone_numbers"_s), phoneNumbers)) {
        call->finishWithText(i18n("Argument phone_numbers must be an array of strings"), true);
        return;
    }

    if (const QString birthdayStr = arguments.value(u"birthday"_s).toString().trimmed(); !birthdayStr.isEmpty()) {
        const QDate birthday = QDate::fromString(birthdayStr, Qt::ISODate);
        if (!birthday.isValid()) {
            call->finishWithText(i18n("Invalid birthday \"%1\", expected format is YYYY-MM-DD", birthdayStr), true);
            return;
        }
    }

    // TODO implement it
    call->finishWithText(i18n("Not implemented yet"), true);
}

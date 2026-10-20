/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "updatecontacttool.h"
#include "common/toolutils.h"
#include "updatecontacttooljob.h"
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
             McpProtocolServerTool::schemaArrayProperty(
                 McpProtocolServerTool::schemaProperty(u"string"_s, {}),
                 u"Email addresses, the first one is the preferred one. Replaces the existing ones, an empty array removes them all"_s)},
            {u"phone_numbers"_s,
             McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}),
                                                        u"Phone numbers. Replaces the existing ones, an empty array removes them all"_s)},
            {u"organization"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Organization of the contact, an empty string clears it"_s)},
            {u"birthday"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Birthday in ISO format (YYYY-MM-DD), an empty string clears it"_s)},
            {u"note"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Free text note, an empty string clears it"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(true);
    annotation.setIdempotentHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Update Contact"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Contact);
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

    UpdateContactToolJob::ContactChanges changes;

    if (const QJsonValue nameValue = arguments.value(u"name"_s); ToolUtils::isProvided(nameValue)) {
        const QString name = nameValue.toString().trimmed();
        if (!nameValue.isString() || name.isEmpty()) {
            call->finishWithText(i18n("Argument name must be a non-empty string"), true);
            return;
        }
        changes.name = name;
    }

    if (const QJsonValue emailsValue = arguments.value(u"emails"_s); ToolUtils::isProvided(emailsValue)) {
        QStringList emails;
        if (!ToolUtils::readStringList(emailsValue, emails)) {
            call->finishWithText(i18n("Argument emails must be an array of strings"), true);
            return;
        }
        changes.emails = emails;
    }

    if (const QJsonValue phoneNumbersValue = arguments.value(u"phone_numbers"_s); ToolUtils::isProvided(phoneNumbersValue)) {
        QStringList phoneNumbers;
        if (!ToolUtils::readStringList(phoneNumbersValue, phoneNumbers)) {
            call->finishWithText(i18n("Argument phone_numbers must be an array of strings"), true);
            return;
        }
        changes.phoneNumbers = phoneNumbers;
    }

    if (!ToolUtils::readOptionalString(arguments, u"organization"_s, changes.organization)) {
        call->finishWithText(i18n("Argument organization must be a string"), true);
        return;
    }

    if (!ToolUtils::readOptionalString(arguments, u"note"_s, changes.note)) {
        call->finishWithText(i18n("Argument note must be a string"), true);
        return;
    }

    std::optional<QString> birthdayStr;
    if (!ToolUtils::readOptionalString(arguments, u"birthday"_s, birthdayStr)) {
        call->finishWithText(i18n("Argument birthday must be a string"), true);
        return;
    }
    if (birthdayStr) {
        // An empty string clears the birthday
        const QDate birthday = QDate::fromString(*birthdayStr, Qt::ISODate);
        if (!birthdayStr->isEmpty() && !birthday.isValid()) {
            call->finishWithText(i18n("Invalid birthday \"%1\", expected format is YYYY-MM-DD", *birthdayStr), true);
            return;
        }
        changes.birthday = birthday;
    }

    if (changes.isEmpty()) {
        call->finishWithText(i18n("No field to update"), true);
        return;
    }

    auto job = new UpdateContactToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->setChanges(changes);
    job->start();
}

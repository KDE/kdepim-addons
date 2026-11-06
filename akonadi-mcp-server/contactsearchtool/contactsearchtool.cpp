/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactsearchtool.h"
#include "common/toolutils.h"
#include "contactsearchtooljob.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;
ContactSearchTool::ContactSearchTool() = default;
ContactSearchTool::~ContactSearchTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ContactSearchTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_search"_s,
        i18n("Search Contacts"),
        u"Search contacts in the Akonadi address books by name or email address"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::ReadOnly,
        QMap<QString, QJsonObject>{
            {u"query"_s, TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"string"_s, u"Name or email address to search for"_s)},
            {u"fields"_s,
             McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaEnumProperty({u"email"_s, u"phone"_s, u"location"_s, u"birthday"_s}, {}),
                                                        u"Contact fields to return"_s)}},
        {u"query"_s});
    ToolUtils::addToolMeta(tool, ToolUtils::Contact);
    return tool;
}

void ContactSearchTool::doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const QString query = call->arguments().value(u"query"_s).toString().trimmed();
    if (query.isEmpty()) {
        call->finishWithText(i18n("Argument query must be a non-empty string"), true);
        return;
    }
    ContactSearchToolJob::ContactFields contactFields = ContactSearchToolJob::ContactField::All;
    const QJsonValue fields = call->arguments().value(u"fields"_s);
    if (fields.isArray()) {
        contactFields = ContactSearchToolJob::ContactField::None;
        const QJsonArray fieldsArray = fields.toArray();
        for (const QJsonValue &field : fieldsArray) {
            const QString fieldName = field.toString();
            if (fieldName == "email"_L1) {
                contactFields |= ContactSearchToolJob::ContactField::Email;
            } else if (fieldName == "phone"_L1) {
                contactFields |= ContactSearchToolJob::ContactField::Phone;
            } else if (fieldName == "location"_L1) {
                contactFields |= ContactSearchToolJob::ContactField::Location;
            } else if (fieldName == "birthday"_L1) {
                contactFields |= ContactSearchToolJob::ContactField::Birthday;
            } else {
                call->finishWithText(i18n("Unknown contact field: %1", fieldName), true);
                return;
            }
        }
    } else if (TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(fields)) {
        call->finishWithText(i18n("Argument fields must be an array"), true);
        return;
    }

    auto job = new ContactSearchToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setNameOrEmail(query);
    job->setFields(contactFields);
    job->start();
}

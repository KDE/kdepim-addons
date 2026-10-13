/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "contactsearchtool.h"
#include "contactsearchtooljob.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;
ContactSearchTool::ContactSearchTool() = default;
ContactSearchTool::~ContactSearchTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ContactSearchTool::definition() const
{
    return TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_search"_s,
        u"Search contacts in the Akonadi address books by name or email address"_s,
        QMap<QString, QJsonObject>{
            {u"query"_s, TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"string"_s, u"Name or email address to search for"_s)},
            {u"fields"_s,
             McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaEnumProperty({u"email"_s, u"phone"_s, u"location"_s, u"birthday"_s}, {}),
                                                        u"Contact fields to return"_s)}},
        {u"query"_s});
}

void ContactSearchTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const QString query = call->arguments().value(u"query"_s).toString().trimmed();
    if (query.isEmpty()) {
        call->finishWithText(i18n("Argument query must be a non-empty string"), true);
        return;
    }
    const QJsonValue fields = call->arguments().value(u"fields"_s);
    if (fields.isUndefined()) {
        // ALL
    } else if (fields.isArray()) {
        // Extract QJsonArray
    } else {
        call->finishWithText(i18n("Argument fields must be an array"), true);
        return;
    }

    // TODO search in akonadi the user (asynchronous job: kill it on call->cancelled(), answer with call->finishWithText())
    call->finishWithText(i18n("Contact search is not implemented yet"), true);
}
/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deletecontacttool.h"
#include "deletecontacttooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

DeleteContactTool::DeleteContactTool() = default;
DeleteContactTool::~DeleteContactTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool DeleteContactTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_delete"_s,
        u"Delete a contact from an Akonadi address book. This cannot be undone"_s,
        QMap<QString, QJsonObject>{{u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Identifier of the contact item (see contact_search)"_s)}},
        {u"id"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(true);
    annotation.setIdempotentHint(true);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("Delete Contact"));
    tool.setAnnotations(annotation);
    return tool;
}

void DeleteContactTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const QJsonValue idValue = call->arguments().value(u"id"_s);
    if (!idValue.isDouble()) {
        call->finishWithText(i18n("Argument id must be an integer"), true);
        return;
    }
    const qint64 itemId = idValue.toInteger(-1);
    if (itemId < 0) {
        call->finishWithText(i18n("Argument id must be a positive integer"), true);
        return;
    }

    auto job = new DeleteContactToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setItemId(itemId);
    job->start();
}

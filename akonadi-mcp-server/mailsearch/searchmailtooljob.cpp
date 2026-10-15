/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "searchmailtooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

SearchMailToolJob::SearchMailToolJob(QObject *parent)
    : QObject{parent}
{
}

SearchMailToolJob::~SearchMailToolJob() = default;

bool SearchMailToolJob::canStart() const
{
    // TODO
    return false;
}

void SearchMailToolJob::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void SearchMailToolJob::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "ContactSearchToolJob can't start";
        if (mToolCall) {
            mToolCall->finishWithText(i18n("Search string must be a non-empty string"), true);
        }
        deleteLater();
        return;
    }

    // TODO
    deleteLater();
}

#include "moc_searchmailtooljob.cpp"

/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contactsearchtooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <Akonadi/ContactSearchJob>
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

ContactSearchToolJob::ContactSearchToolJob(QObject *parent)
    : QObject{parent}
{
}

ContactSearchToolJob::~ContactSearchToolJob() = default;

void ContactSearchToolJob::setNameOrEmail(const QString &str)
{
    mSearchString = str;
}

bool ContactSearchToolJob::canStart() const
{
    return !mSearchString.isEmpty() && mToolCall;
}

void ContactSearchToolJob::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "ContactSearchToolJob can't start";
        if (mToolCall) {
            mToolCall->finishWithText(i18n("Search string must be a non-empty string"), true);
        }
        deleteLater();
        return;
    }

    auto job = new Akonadi::ContactSearchJob(this);
    job->setQuery(Akonadi::ContactSearchJob::NameOrEmail, mSearchString, Akonadi::ContactSearchJob::ContainsMatch);
    connect(job, &KJob::result, this, &ContactSearchToolJob::slotResult);
}

void ContactSearchToolJob::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void ContactSearchToolJob::slotResult(KJob *job)
{
    // TODO
    deleteLater();
}
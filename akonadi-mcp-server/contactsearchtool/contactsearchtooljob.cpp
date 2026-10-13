/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contactsearchtooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <Akonadi/ContactSearchJob>
#include <KJob>
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;

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

    mSearchJob = new Akonadi::ContactSearchJob(this);
    mSearchJob->setQuery(Akonadi::ContactSearchJob::NameOrEmail, mSearchString, Akonadi::ContactSearchJob::ContainsMatch);
    connect(mSearchJob, &KJob::result, this, &ContactSearchToolJob::slotResult);
    connect(mToolCall, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall::cancelled, this, &ContactSearchToolJob::slotCancelled);
}

void ContactSearchToolJob::slotCancelled()
{
    if (mSearchJob) {
        mSearchJob->kill();
    }
    deleteLater();
}

void ContactSearchToolJob::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void ContactSearchToolJob::slotResult(KJob *job)
{
    if (!mToolCall) {
        deleteLater();
        return;
    }
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Contact search failed:" << job->errorString();
        mToolCall->finishWithText(i18n("Contact search failed: %1", job->errorString()), true);
        deleteLater();
        return;
    }
    const KContacts::Addressee::List contacts = qobject_cast<Akonadi::ContactSearchJob *>(job)->contacts();
    if (contacts.isEmpty()) {
        mToolCall->finishWithText(i18n("No contact found for \"%1\"", mSearchString));
        deleteLater();
        return;
    }
    QStringList lines;
    lines.reserve(contacts.count());
    for (const KContacts::Addressee &contact : contacts) {
        lines.append(contact.formattedName() + u" <"_s + contact.emails().join(u", "_s) + u'>');
    }
    mToolCall->finishWithText(lines.join(u'\n'));
    deleteLater();
}

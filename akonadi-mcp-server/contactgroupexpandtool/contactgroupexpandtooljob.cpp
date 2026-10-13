/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contactgroupexpandtooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <Akonadi/ContactGroupExpandJob>
#include <Akonadi/ContactGroupSearchJob>
#include <KJob>
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;

ContactGroupExpandToolJob::ContactGroupExpandToolJob(QObject *parent)
    : QObject{parent}
{
}

ContactGroupExpandToolJob::~ContactGroupExpandToolJob() = default;

void ContactGroupExpandToolJob::setGroupName(const QString &str)
{
    mSearchString = str;
}

bool ContactGroupExpandToolJob::canStart() const
{
    return !mSearchString.isEmpty() && mToolCall;
}

void ContactGroupExpandToolJob::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "ContactGroupExpandToolJob can't start";
        if (mToolCall) {
            mToolCall->finishWithText(i18n("Search string must be a non-empty string"), true);
        }
        deleteLater();
        return;
    }

    mSearchJob = new Akonadi::ContactGroupSearchJob(this);
    mSearchJob->setQuery(Akonadi::ContactGroupSearchJob::Name, mSearchString, Akonadi::ContactGroupSearchJob::ContainsMatch);
    connect(mSearchJob, &KJob::result, this, &ContactGroupExpandToolJob::slotResult);
    connect(mToolCall, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall::cancelled, this, &ContactGroupExpandToolJob::slotCancelled);
}

void ContactGroupExpandToolJob::slotCancelled()
{
    if (mSearchJob) {
        mSearchJob->kill();
    }
    if (mExpandJob) {
        mExpandJob->kill();
    }
    deleteLater();
}

void ContactGroupExpandToolJob::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void ContactGroupExpandToolJob::finish(const QString &text, bool isError)
{
    if (mToolCall) {
        mToolCall->finishWithText(text, isError);
    }
    deleteLater();
}

void ContactGroupExpandToolJob::slotResult(KJob *job)
{
    if (!mToolCall) {
        deleteLater();
        return;
    }
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Contact group search failed:" << job->errorString();
        finish(i18n("Contact group search failed: %1", job->errorString()), true);
        return;
    }
    mContactGroups = qobject_cast<Akonadi::ContactGroupSearchJob *>(job)->contactGroups();
    if (mContactGroups.isEmpty()) {
        finish(i18n("No contact group found for \"%1\"", mSearchString));
        return;
    }
    mEntries.reserve(mContactGroups.count());
    expandNextGroup();
}

void ContactGroupExpandToolJob::expandNextGroup()
{
    if (!mToolCall) {
        deleteLater();
        return;
    }
    if (mContactGroups.isEmpty()) {
        finish(mEntries.join(u'\n'));
        return;
    }
    mExpandJob = new Akonadi::ContactGroupExpandJob(mContactGroups.constFirst(), this);
    connect(mExpandJob, &KJob::result, this, &ContactGroupExpandToolJob::slotExpandResult);
    mExpandJob->start();
}

void ContactGroupExpandToolJob::slotExpandResult(KJob *job)
{
    const KContacts::ContactGroup contactGroup = mContactGroups.takeFirst();
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Contact group expand failed:" << contactGroup.name() << job->errorString();
        mEntries.append(i18n("%1: expand failed: %2", contactGroup.name(), job->errorString()));
        expandNextGroup();
        return;
    }
    const KContacts::Addressee::List contacts = qobject_cast<Akonadi::ContactGroupExpandJob *>(job)->contacts();
    QStringList lines{contactGroup.name()};
    lines.reserve(contacts.count() + 1);
    for (const KContacts::Addressee &contact : contacts) {
        if (contact.preferredEmail().isEmpty()) {
            lines.append(contact.realName());
        } else {
            lines.append(contact.fullEmail());
        }
    }
    mEntries.append(lines.join(u"\n  "_s));
    expandNextGroup();
}

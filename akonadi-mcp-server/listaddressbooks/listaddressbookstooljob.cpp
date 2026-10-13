/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "listaddressbookstooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <KContacts/Addressee>
#include <KContacts/ContactGroup>
#include <KJob>
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;

ListAddressBooksToolJob::ListAddressBooksToolJob(QObject *parent)
    : QObject{parent}
{
}

ListAddressBooksToolJob::~ListAddressBooksToolJob() = default;

bool ListAddressBooksToolJob::canStart() const
{
    return mToolCall;
}

void ListAddressBooksToolJob::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "ListAddressBooksToolJob can't start";
        deleteLater();
        return;
    }

    mFetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);
    mFetchJob->fetchScope().setContentMimeTypes({KContacts::Addressee::mimeType(), KContacts::ContactGroup::mimeType()});
    connect(mFetchJob, &KJob::result, this, &ListAddressBooksToolJob::slotResult);
    connect(mToolCall, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall::cancelled, this, &ListAddressBooksToolJob::slotCancelled);
}

void ListAddressBooksToolJob::slotCancelled()
{
    if (mFetchJob) {
        mFetchJob->kill();
    }
    deleteLater();
}

void ListAddressBooksToolJob::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void ListAddressBooksToolJob::slotResult(KJob *job)
{
    if (!mToolCall) {
        deleteLater();
        return;
    }
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Address book fetch failed:" << job->errorString();
        mToolCall->finishWithText(i18n("Address book fetch failed: %1", job->errorString()), true);
        deleteLater();
        return;
    }
    const Akonadi::Collection::List collections = qobject_cast<Akonadi::CollectionFetchJob *>(job)->collections();
    QStringList entries;
    entries.reserve(collections.count());
    for (const Akonadi::Collection &collection : collections) {
        if (collection.isVirtual()) {
            continue;
        }
        const QStringList mimeTypes = collection.contentMimeTypes();
        if (!mimeTypes.contains(KContacts::Addressee::mimeType()) && !mimeTypes.contains(KContacts::ContactGroup::mimeType())) {
            continue;
        }
        QString entry = u"%1 (id: %2)"_s.arg(collection.displayName(), QString::number(collection.id()));
        if (!(collection.rights() & Akonadi::Collection::CanCreateItem)) {
            entry += u" [read-only]"_s;
        }
        entries.append(entry);
    }
    if (entries.isEmpty()) {
        mToolCall->finishWithText(i18n("No address book found"));
    } else {
        mToolCall->finishWithText(entries.join(u'\n'));
    }
    deleteLater();
}

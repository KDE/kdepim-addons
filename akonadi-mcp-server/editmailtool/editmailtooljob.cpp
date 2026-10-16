/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "editmailtooljob.h"
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/SpecialMailCollections>
#include <Akonadi/SpecialMailCollectionsRequestJob>
#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/IdentityManager>
#include <KJob>
#include <KLocalizedString>
#include <QDBusMessage>
#include <QDBusPendingReply>

using namespace Qt::Literals::StringLiterals;

EditMailToolJob::EditMailToolJob(QObject *parent)
    : KMailDBusToolJobBase{parent}
{
}

EditMailToolJob::~EditMailToolJob() = default;

void EditMailToolJob::setItemId(qint64 id)
{
    mItemId = id;
}

bool EditMailToolJob::canStart() const
{
    return KMailDBusToolJobBase::canStart() && mItemId >= 0;
}

QString EditMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Mail id must be a positive integer");
}

void EditMailToolJob::startJob()
{
    // KMail only edits mails stored in a Drafts folder but reports it asynchronously, so check it before the D-Bus call
    auto fetchJob = new Akonadi::ItemFetchJob(Akonadi::Item(mItemId), this);
    fetchJob->fetchScope().setAncestorRetrieval(Akonadi::ItemFetchScope::Parent);
    connect(fetchJob, &KJob::result, this, &EditMailToolJob::slotItemFetchResult);
    setCurrentJob(fetchJob);
}

void EditMailToolJob::slotItemFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Mail fetch failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemFetchJob *>(job)->items();
    if (items.isEmpty()) {
        finish(i18n("Mail %1 not found", mItemId), true);
        return;
    }
    mParentCollection = items.constFirst().parentCollection();

    // Same check as MailCommon::Kernel::folderIsDrafts(): drafts folder of an identity or default Drafts folder
    const QString collectionId = QString::number(mParentCollection.id());
    const KIdentityManagementCore::IdentityManager *identityManager = KIdentityManagementCore::IdentityManager::self();
    for (auto it = identityManager->begin(), end = identityManager->end(); it != end; ++it) {
        if ((*it).drafts() == collectionId) {
            KMailDBusToolJobBase::startJob();
            return;
        }
    }

    auto requestJob = new Akonadi::SpecialMailCollectionsRequestJob(this);
    requestJob->requestDefaultCollection(Akonadi::SpecialMailCollections::Drafts);
    connect(requestJob, &KJob::result, this, &EditMailToolJob::slotDraftsCollectionResult);
    setCurrentJob(requestJob);
}

void EditMailToolJob::slotDraftsCollectionResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Drafts folder fetch failed: %1"))) {
        return;
    }
    const Akonadi::Collection draftsCollection = qobject_cast<Akonadi::SpecialMailCollectionsRequestJob *>(job)->collection();
    if (!draftsCollection.isValid() || draftsCollection != mParentCollection) {
        finish(i18n("Mail %1 is not stored in a Drafts folder, it can't be edited. Use open_mail or reply_mail instead", mItemId), true);
        return;
    }
    KMailDBusToolJobBase::startJob();
}

QDBusMessage EditMailToolJob::kmailMethodCall() const
{
    QDBusMessage message = createKMailMethodCall(u"editMail"_s);
    message << mItemId;
    return message;
}

QString EditMailToolJob::kmailCallErrorMessage(const QString &error) const
{
    return i18n("Unable to edit mail %1: %2", mItemId, error);
}

void EditMailToolJob::kmailCallFinished(const QDBusPendingCall &reply)
{
    const QDBusPendingReply<bool> editMailReply = reply;
    if (!editMailReply.value()) {
        finish(i18n("Unable to edit mail %1: KMail main window is not available", mItemId), true);
        return;
    }
    finish(i18n("Draft mail %1 opened in a KMail composer", mItemId));
}

#include "moc_editmailtooljob.cpp"

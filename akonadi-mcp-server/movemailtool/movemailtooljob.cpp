/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "movemailtooljob.h"
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemMoveJob>
#include <KLocalizedString>
#include <KMime/Message>
#include <QHash>

using namespace Qt::Literals::StringLiterals;

namespace
{
// Path of the collection from its top-level (resource) collection, separated by '/'
[[nodiscard]] QString collectionPath(const Akonadi::Collection &collection, const QHash<Akonadi::Collection::Id, Akonadi::Collection> &collections)
{
    QStringList names{collection.displayName()};
    Akonadi::Collection::Id parentId = collection.parentCollection().id();
    // Bound the walk in case of an inconsistent tree
    for (int depth = 0; depth < collections.size(); ++depth) {
        const auto it = collections.constFind(parentId);
        if (it == collections.cend()) {
            break;
        }
        names.prepend(it->displayName());
        parentId = it->parentCollection().id();
    }
    return names.join(u'/');
}
}

MoveMailToolJob::MoveMailToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

MoveMailToolJob::~MoveMailToolJob() = default;

bool MoveMailToolJob::canStart() const
{
    return ToolJobBase::canStart() && mItemId >= 0 && ((mFolderId >= 0) != !mFolder.isEmpty());
}

void MoveMailToolJob::setItemId(qint64 itemId)
{
    mItemId = itemId;
}

void MoveMailToolJob::setFolderId(qint64 folderId)
{
    mFolderId = folderId;
}

void MoveMailToolJob::setFolder(const QString &folder)
{
    mFolder = folder;
}

QString MoveMailToolJob::invalidArgumentsMessage() const
{
    if (mItemId < 0) {
        return i18n("Mail id must be a positive integer");
    }
    return i18n("Exactly one of folder or folder_id must be given");
}

void MoveMailToolJob::startJob()
{
    auto fetchJob = new Akonadi::ItemFetchJob(Akonadi::Item(mItemId), this);
    fetchJob->fetchScope().fetchFullPayload(false);
    connect(fetchJob, &KJob::result, this, &MoveMailToolJob::slotItemFetchResult);
    setCurrentJob(fetchJob);
}

void MoveMailToolJob::slotItemFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Mail fetch failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemFetchJob *>(job)->items();
    if (items.isEmpty()) {
        finish(i18n("Mail %1 not found", mItemId), true);
        return;
    }
    mItem = items.at(0);
    if (mItem.mimeType() != KMime::Message::mimeType()) {
        finish(i18n("Item %1 is not a mail", mItemId), true);
        return;
    }

    // Fetch all mail folders: needed to resolve a name and to check the destination
    auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);
    fetchJob->fetchScope().setContentMimeTypes({KMime::Message::mimeType()});
    connect(fetchJob, &KJob::result, this, &MoveMailToolJob::slotCollectionFetchResult);
    setCurrentJob(fetchJob);
}

void MoveMailToolJob::slotCollectionFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Mail folder fetch failed: %1"))) {
        return;
    }
    const Akonadi::Collection::List collections = qobject_cast<Akonadi::CollectionFetchJob *>(job)->collections();
    QHash<Akonadi::Collection::Id, Akonadi::Collection> collectionById;
    collectionById.reserve(collections.count());
    for (const Akonadi::Collection &collection : collections) {
        collectionById.insert(collection.id(), collection);
    }

    const auto isMailFolder = [](const Akonadi::Collection &collection) {
        return !collection.isVirtual() && collection.contentMimeTypes().contains(KMime::Message::mimeType());
    };

    if (mFolderId >= 0) {
        const auto it = collectionById.constFind(mFolderId);
        if (it == collectionById.cend() || !isMailFolder(*it)) {
            finish(i18n("Mail folder %1 not found", mFolderId), true);
            return;
        }
        moveItem(*it, collectionPath(*it, collectionById));
        return;
    }

    // An exact path match wins over a name match
    QList<std::pair<Akonadi::Collection, QString>> pathMatches;
    QList<std::pair<Akonadi::Collection, QString>> nameMatches;
    for (const Akonadi::Collection &collection : collections) {
        if (!isMailFolder(collection)) {
            continue;
        }
        const QString path = collectionPath(collection, collectionById);
        if (path.compare(mFolder, Qt::CaseInsensitive) == 0) {
            pathMatches.append({collection, path});
        } else if (collection.displayName().compare(mFolder, Qt::CaseInsensitive) == 0) {
            nameMatches.append({collection, path});
        }
    }
    const auto &matches = pathMatches.isEmpty() ? nameMatches : pathMatches;
    if (matches.isEmpty()) {
        finish(i18n("Mail folder \"%1\" not found", mFolder), true);
        return;
    }
    if (matches.count() > 1) {
        QStringList candidates;
        candidates.reserve(matches.count());
        for (const auto &[collection, path] : matches) {
            candidates.append(u"%1 (folder_id: %2)"_s.arg(path, QString::number(collection.id())));
        }
        finish(i18n("Several mail folders match \"%1\", use the full path or folder_id:\n%2", mFolder, candidates.join(u'\n')), true);
        return;
    }
    moveItem(matches.constFirst().first, matches.constFirst().second);
}

void MoveMailToolJob::moveItem(const Akonadi::Collection &destination, const QString &destinationName)
{
    if (mItem.parentCollection().id() == destination.id()) {
        finish(i18n("Mail %1 is already in folder \"%2\"", mItemId, destinationName));
        return;
    }
    if (!(destination.rights() & Akonadi::Collection::CanCreateItem)) {
        finish(i18n("Mail folder \"%1\" is read-only", destinationName), true);
        return;
    }
    auto moveJob = new Akonadi::ItemMoveJob(mItem, destination, this);
    moveJob->setProperty("destinationName", destinationName);
    connect(moveJob, &KJob::result, this, &MoveMailToolJob::slotItemMoveResult);
    setCurrentJob(moveJob);
}

void MoveMailToolJob::slotItemMoveResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Mail move failed: %1"))) {
        return;
    }
    finish(i18n("Mail %1 moved to folder \"%2\"", mItemId, job->property("destinationName").toString()));
}

#include "moc_movemailtooljob.cpp"

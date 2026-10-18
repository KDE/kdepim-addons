/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markmailtooljob.h"
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemModifyJob>
#include <Akonadi/MessageFlags>
#include <KLocalizedString>

MarkMailToolJob::MarkMailToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

MarkMailToolJob::~MarkMailToolJob() = default;

bool MarkMailToolJob::canStart() const
{
    return ToolJobBase::canStart() && mItemId >= 0;
}

void MarkMailToolJob::setItemId(qint64 newItemId)
{
    mItemId = newItemId;
}

void MarkMailToolJob::setRead(std::optional<bool> read)
{
    mRead = read;
}

void MarkMailToolJob::setImportant(std::optional<bool> important)
{
    mImportant = important;
}

QString MarkMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Mail id must be a positive integer");
}

void MarkMailToolJob::startJob()
{
    auto fetchJob = new Akonadi::ItemFetchJob(Akonadi::Item(mItemId), this);
    fetchJob->fetchScope().fetchFullPayload(false);
    connect(fetchJob, &KJob::result, this, &MarkMailToolJob::slotItemFetchResult);
    setCurrentJob(fetchJob);
}

void MarkMailToolJob::slotItemFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Mail fetch failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemFetchJob *>(job)->items();
    if (items.isEmpty()) {
        finish(i18n("Mail %1 not found", mItemId), true);
        return;
    }
    Akonadi::Item item = items.at(0);
    applyFlag(item, Akonadi::MessageFlags::Seen, mRead);
    applyFlag(item, Akonadi::MessageFlags::Flagged, mImportant);
    auto modifyJob = new Akonadi::ItemModifyJob(item, this);
    connect(modifyJob, &KJob::result, this, &MarkMailToolJob::slotItemModifyResult);
    modifyJob->setIgnorePayload(true);
    setCurrentJob(modifyJob);
}

void MarkMailToolJob::slotItemModifyResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Mail modification failed: %1"))) {
        return;
    }
    finish(i18n("Mail %1 modified", mItemId));
}

void MarkMailToolJob::applyFlag(Akonadi::Item &item, const QByteArray &flag, std::optional<bool> value)
{
    if (!value) {
        return;
    }
    if (*value) {
        item.setFlag(flag);
    } else {
        item.clearFlag(flag);
    }
}

#include "moc_markmailtooljob.cpp"

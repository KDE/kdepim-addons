/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markmailtooljob.h"
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemModifyJob>

MarkMailToolJob::MarkMailToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

MarkMailToolJob::~MarkMailToolJob() = default;

bool MarkMailToolJob::canStart() const
{
    return mItemId >= 0;
}

qint64 MarkMailToolJob::itemId() const
{
    return mItemId;
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

void MarkMailToolJob::startJob()
{
    // TODO
}

#include "moc_markmailtooljob.cpp"

/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markmailtooljob.h"

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

void MarkMailToolJob::startJob()
{
}

#include "moc_markmailtooljob.cpp"

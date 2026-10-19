/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/tooljobbase.h"
#include <Akonadi/Collection>
#include <Akonadi/Item>

class MoveMailToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit MoveMailToolJob(QObject *parent = nullptr);
    ~MoveMailToolJob() override;

    [[nodiscard]] bool canStart() const override;

    void setItemId(qint64 itemId);
    // Destination given by id, otherwise by folder name or path
    void setFolderId(qint64 folderId);
    void setFolder(const QString &folder);

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotItemFetchResult(KJob *job);
    void slotCollectionFetchResult(KJob *job);
    void slotItemMoveResult(KJob *job);
    void moveItem(const Akonadi::Collection &destination, const QString &destinationName);
    qint64 mItemId = -1;
    qint64 mFolderId = -1;
    QString mFolder;
    Akonadi::Item mItem;
};

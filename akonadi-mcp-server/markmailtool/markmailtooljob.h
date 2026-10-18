/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/tooljobbase.h"
#include <optional>

namespace Akonadi
{
class Item;
}

class MarkMailToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit MarkMailToolJob(QObject *parent = nullptr);
    ~MarkMailToolJob() override;

    [[nodiscard]] bool canStart() const override;

    void setItemId(qint64 newItemId);

    void setRead(std::optional<bool> read);
    void setImportant(std::optional<bool> important);

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotItemFetchResult(KJob *job);
    void applyFlag(Akonadi::Item &item, const QByteArray &flag, std::optional<bool> value);
    void slotItemModifyResult(KJob *job);
    qint64 mItemId = -1;
    std::optional<bool> mRead;
    std::optional<bool> mImportant;
};

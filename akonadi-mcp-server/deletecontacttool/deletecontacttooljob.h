/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/tooljobbase.h"

class DeleteContactToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit DeleteContactToolJob(QObject *parent = nullptr);
    ~DeleteContactToolJob() override;

    [[nodiscard]] bool canStart() const override;

    void setItemId(qint64 itemId);

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotItemFetchResult(KJob *job);
    void slotItemDeleteResult(KJob *job);
    qint64 mItemId = -1;
};

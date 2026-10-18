/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/tooljobbase.h"

class MarkMailToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit MarkMailToolJob(QObject *parent = nullptr);
    ~MarkMailToolJob() override;

    [[nodiscard]] bool canStart() const override;

    [[nodiscard]] qint64 itemId() const;
    void setItemId(qint64 newItemId);

    void setRead(std::optional<bool> read);
    void setImportant(std::optional<bool> important);

protected:
    void startJob() override;

private:
    qint64 mItemId = -1;
    std::optional<bool> mRead;
    std::optional<bool> mImportant;
};

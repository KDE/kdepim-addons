/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"

class UpcomingBirthdaysToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit UpcomingBirthdaysToolJob(QObject *parent = nullptr);
    ~UpcomingBirthdaysToolJob() override;

    void setDays(int days);

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotResult(KJob *job);
    int mDays = 30;
};

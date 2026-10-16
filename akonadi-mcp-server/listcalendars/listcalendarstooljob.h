/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"

class ListCalendarsToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit ListCalendarsToolJob(QObject *parent = nullptr);
    ~ListCalendarsToolJob() override;

protected:
    void startJob() override;

private:
    void slotResult(KJob *job);
};

/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"
#include <KCalendarCore/Calendar>

class CalendarToolJobBase : public ToolJobBase
{
    Q_OBJECT
public:
    explicit CalendarToolJobBase(QObject *parent = nullptr);
    ~CalendarToolJobBase() override;

protected:
    void startJob() override;
    [[nodiscard]] virtual QStringList mimeTypes() const = 0;
    [[nodiscard]] virtual QString generateResult(const KCalendarCore::Calendar::Ptr &calendar) const = 0;

private:
    void slotResult(KJob *job);
};

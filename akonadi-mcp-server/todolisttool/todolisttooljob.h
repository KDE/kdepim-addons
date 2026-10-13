/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "calendarcommon/calendartooljobbase.h"

class TodoListToolJob : public CalendarToolJobBase
{
public:
    explicit TodoListToolJob(QObject *parent = nullptr);
    ~TodoListToolJob() override;

    void setIncludeCompleted(bool includeCompleted);
    // 0 means no limit
    void setDueWithinDays(int days);

protected:
    [[nodiscard]] QStringList mimeTypes() const override;
    [[nodiscard]] QString generateResult(const KCalendarCore::Calendar::Ptr &calendar) const override;

private:
    int mDueWithinDays = 0;
    bool mIncludeCompleted = false;
};

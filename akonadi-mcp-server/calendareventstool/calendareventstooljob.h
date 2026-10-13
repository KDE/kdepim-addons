/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "calendarcommon/calendartooljobbase.h"
#include <QDateTime>

class CalendarEventsToolJob : public CalendarToolJobBase
{
public:
    explicit CalendarEventsToolJob(QObject *parent = nullptr);
    ~CalendarEventsToolJob() override;

    void setStart(const QDateTime &start);
    void setEnd(const QDateTime &end);

    [[nodiscard]] bool canStart() const override;

protected:
    [[nodiscard]] QStringList mimeTypes() const override;
    [[nodiscard]] QString generateResult(const KCalendarCore::Calendar::Ptr &calendar) const override;

private:
    QDateTime mStart;
    QDateTime mEnd;
};

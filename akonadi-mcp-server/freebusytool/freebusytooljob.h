/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "calendarcommon/calendartooljobbase.h"
#include <QDateTime>

class FreeBusyToolJob : public CalendarToolJobBase
{
public:
    explicit FreeBusyToolJob(QObject *parent = nullptr);
    ~FreeBusyToolJob() override;

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

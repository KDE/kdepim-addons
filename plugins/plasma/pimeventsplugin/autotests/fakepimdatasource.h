/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#pragma once

#include "pimdatasource.h"

class FakePimDataSource : public PimDataSource
{
public:
    FakePimDataSource();
    ~FakePimDataSource() override;

    void setAkonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence, qint64 akonadiId);
    [[nodiscard]] qint64 akonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const override;

    [[nodiscard]] KCalendarCore::Calendar *calendar() const override;

    [[nodiscard]] QString calendarColorForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const override;

private:
    QMap<KCalendarCore::Incidence::Ptr, qint64> mAkonadiIdMap;
    KCalendarCore::Calendar *mCalendar = nullptr;
};

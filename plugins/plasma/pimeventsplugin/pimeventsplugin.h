/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#pragma once

#include <CalendarEvents/CalendarEventsPlugin>
#include <KCalendarCore/Calendar>

namespace Akonadi
{
class ETMCalendar;
}

class PimDataSource;
class PimEventsPlugin : public CalendarEvents::CalendarEventsPlugin, public KCalendarCore::Calendar::CalendarObserver
{
    Q_OBJECT
    Q_INTERFACES(CalendarEvents::CalendarEventsPlugin)
    Q_PLUGIN_METADATA(IID "org.kde.CalendarEventsPlugin" FILE "pimeventsplugin.json")

public:
    explicit PimEventsPlugin(QObject *parent = nullptr);
    explicit PimEventsPlugin(PimDataSource *factory, QObject *parent = nullptr);
    ~PimEventsPlugin() override;

    // CalendarEvents::CalendarEventsPlugin
    void loadEventsForDateRange(const QDate &startDate, const QDate &endDate) override;

    // KCalendarCore::Calendar::CalendarObserver
    void calendarIncidenceChanged(const KCalendarCore::Incidence::Ptr &incidence) override;
    void calendarIncidenceAdded(const KCalendarCore::Incidence::Ptr &incidence) override;
    // Handle removal before it really happens otherwise we would not be able
    // to lookup corresponding Akonadi ID in ETMCalendar
    void calendarIncidenceAboutToBeDeleted(const KCalendarCore::Incidence::Ptr &incidence) override;

private:
    PimDataSource *const mDataSource;
    QDate mStart;
    QDate mEnd;
};


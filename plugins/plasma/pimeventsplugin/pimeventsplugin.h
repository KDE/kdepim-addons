/*
 * Copyright (C) 2016  Daniel Vrátil <dvratil@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef PIMEVENTSPLUGIN_H
#define PIMEVENTSPLUGIN_H

#include <CalendarEvents/CalendarEventsPlugin>
#include <KCalCore/Calendar>

namespace Akonadi
{
class ETMCalendar;
}

class PimDataSource;
class PimEventsPlugin : public CalendarEvents::CalendarEventsPlugin
                      , public KCalCore::Calendar::CalendarObserver
{
    Q_OBJECT
    Q_INTERFACES(CalendarEvents::CalendarEventsPlugin)
    Q_PLUGIN_METADATA(IID "org.kde.CalendarEventsPlugin" FILE "pimeventsplugin.json")

public:
    explicit PimEventsPlugin(QObject *parent = Q_NULLPTR);
    explicit PimEventsPlugin(PimDataSource *factory, QObject *parent = Q_NULLPTR);
    ~PimEventsPlugin();

    // CalendarEvents::CalendarEventsPlugin
    void loadEventsForDateRange(const QDate &startDate, const QDate &endDate) Q_DECL_OVERRIDE;

    // KCalCore::Calendar::CalendarObserver
    void calendarIncidenceChanged(const KCalCore::Incidence::Ptr &incidence) Q_DECL_OVERRIDE;
    void calendarIncidenceAdded(const KCalCore::Incidence::Ptr &incidence) Q_DECL_OVERRIDE;
    // Handle removal before it really happens otherwise we would not be able
    // to lookup corresponding Akonadi ID in ETMCalendar
    void calendarIncidenceAboutToBeDeleted(const KCalCore::Incidence::Ptr &incidence) Q_DECL_OVERRIDE;

private:
    PimDataSource *mDataSource;
    QDate mStart;
    QDate mEnd;
};

#endif

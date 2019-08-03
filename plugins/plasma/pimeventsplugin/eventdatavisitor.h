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

#ifndef EVENTDATAVISITOR_H
#define EVENTDATAVISITOR_H

#include <KCalendarCore/Visitor>
#include <QMultiHash>
#include <CalendarEvents/CalendarEventsPlugin>

class PimDataSource;
class BaseEventDataVisitor : public KCalendarCore::Visitor
{
public:
    ~BaseEventDataVisitor();

    bool act(const KCalendarCore::Incidence::Ptr &incidence);
    bool act(const KCalendarCore::Event::List &events);
    bool act(const KCalendarCore::Todo::List &todos);

protected:
    BaseEventDataVisitor(PimDataSource *dataSource, const QDate &start, const QDate &end);

    QString generateUid(const KCalendarCore::Incidence::Ptr &incidence, const QDateTime &recurrenceId = {}) const;
    bool isInRange(const QDate &start, const QDate &end) const;

    QVector<CalendarEvents::EventData> explodeIncidenceOccurences(const CalendarEvents::EventData &ed, const KCalendarCore::Incidence::Ptr &incidence, bool &ok);
protected:
    PimDataSource *mDataSource = nullptr;
    QDate mStart;
    QDate mEnd;
};

class EventDataVisitor : public BaseEventDataVisitor
{
public:
    EventDataVisitor(PimDataSource *dataSource, const QDate &start, const QDate &end);
    ~EventDataVisitor() override;

    const QMultiHash<QDate, CalendarEvents::EventData> &results() const;

protected:
    bool visit(const KCalendarCore::Event::Ptr &event) override;
    bool visit(const KCalendarCore::Todo::Ptr &todo) override;
    bool visit(const KCalendarCore::Journal::Ptr &) override
    {
        return false;
    }

    bool visit(const KCalendarCore::FreeBusy::Ptr &) override
    {
        return false;
    }

private:
    void insertResult(const CalendarEvents::EventData &result);

    bool visit(const KCalendarCore::Incidence::Ptr &incidence, CalendarEvents::EventData::EventType eventType);
    CalendarEvents::EventData incidenceData(const KCalendarCore::Incidence::Ptr &incidence) const;

    QMultiHash<QDate, CalendarEvents::EventData> mResults;
};

class EventDataIdVisitor : public BaseEventDataVisitor
{
public:
    explicit EventDataIdVisitor(PimDataSource *dataSource, const QDate &start, const QDate &end);

    const QStringList &results() const;

protected:
    bool visit(const KCalendarCore::Event::Ptr &event) override;
    bool visit(const KCalendarCore::Todo::Ptr &todo) override;
    bool visit(const KCalendarCore::Journal::Ptr &) override
    {
        return false;
    }

    bool visit(const KCalendarCore::FreeBusy::Ptr &) override
    {
        return false;
    }

private:
    bool visit(const KCalendarCore::Incidence::Ptr &incidence);

    QStringList mResults;
};

#endif

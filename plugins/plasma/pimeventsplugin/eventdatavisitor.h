/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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
    BaseEventDataVisitor(PimDataSource *dataSource, QDate start, QDate end);

    QString generateUid(const KCalendarCore::Incidence::Ptr &incidence, const QDateTime &recurrenceId = {}) const;
    bool isInRange(QDate start, QDate end) const;

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
    explicit EventDataIdVisitor(PimDataSource *dataSource, QDate start, QDate end);

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

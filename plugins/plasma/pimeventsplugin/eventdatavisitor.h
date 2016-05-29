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

#include <KCalCore/Visitor>
#include <QMultiHash>
#include <CalendarEvents/CalendarEventsPlugin>

namespace Akonadi
{
class ETMCalendar;
}

class BaseEventDataVisitor : public KCalCore::Visitor
{
public:
    ~BaseEventDataVisitor();

    bool act(const KCalCore::Incidence::Ptr &incidence);
    bool act(const KCalCore::Event::List &events);
    bool act(const KCalCore::Todo::List &todos);

protected:
    BaseEventDataVisitor(Akonadi::ETMCalendar *calendar, const QDate &start, const QDate &end);

    QString generateUid(const KCalCore::Incidence::Ptr &incidence, const KDateTime &recurrenceId = KDateTime()) const;
    bool isInRange(const QDate &start, const QDate &end) const;

    QVector<CalendarEvents::EventData> explodeIncidenceOccurences(const CalendarEvents::EventData &ed,
                                                                  const KCalCore::Incidence::Ptr &incidence,
                                                                  bool &ok);
    // can be overridden by unit-tests
    virtual qint64 itemIdForIncidence(const KCalCore::Incidence::Ptr &incidence) const;

protected:
    Akonadi::ETMCalendar *mCalendar;
    QDate mStart;
    QDate mEnd;
};

class EventDataVisitor : public BaseEventDataVisitor
{
public:
    EventDataVisitor(Akonadi::ETMCalendar *calendar, const QDate &start, const QDate &end);
    ~EventDataVisitor();

    const QMultiHash<QDate, CalendarEvents::EventData> &results() const;

protected:
    bool visit(const KCalCore::Event::Ptr &event) Q_DECL_OVERRIDE;
    bool visit(const KCalCore::Todo::Ptr &todo) Q_DECL_OVERRIDE;
    bool visit(const KCalCore::Journal::Ptr &) Q_DECL_OVERRIDE { return false; }
    bool visit(const KCalCore::FreeBusy::Ptr &) Q_DECL_OVERRIDE { return false; }
private:
    CalendarEvents::EventData incidenceData(const KCalCore::Incidence::Ptr &incidence) const;

    QMultiHash<QDate, CalendarEvents::EventData> mResults;

};


class EventDataIdVisitor : public BaseEventDataVisitor
{
public:
    explicit EventDataIdVisitor(Akonadi::ETMCalendar *calendar, const QDate &start, const QDate &end);

    const QStringList &results() const;

protected:
    bool visit(const KCalCore::Event::Ptr &event) Q_DECL_OVERRIDE;
    bool visit(const KCalCore::Todo::Ptr &todo) Q_DECL_OVERRIDE;
    bool visit(const KCalCore::Journal::Ptr &) Q_DECL_OVERRIDE { return false; }
    bool visit(const KCalCore::FreeBusy::Ptr &) Q_DECL_OVERRIDE { return false; }

private:
    QStringList mResults;
};


#endif

/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "updateincidencetooljob.h"
#include <Akonadi/CalendarUtils>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/ItemModifyJob>
#include <KCalendarCore/Event>
#include <KCalendarCore/Todo>
#include <KLocalizedString>

namespace
{
constexpr int defaultDurationSecs = 3600;
}

bool UpdateIncidenceToolJob::IncidenceChanges::isEmpty() const
{
    return !summary && !description && !location && !start && !end && !due && !priority && !completed;
}

UpdateIncidenceToolJob::UpdateIncidenceToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

UpdateIncidenceToolJob::~UpdateIncidenceToolJob() = default;

bool UpdateIncidenceToolJob::canStart() const
{
    return ToolJobBase::canStart() && mItemId >= 0 && !mChanges.isEmpty();
}

void UpdateIncidenceToolJob::setItemId(qint64 itemId)
{
    mItemId = itemId;
}

void UpdateIncidenceToolJob::setChanges(const IncidenceChanges &changes)
{
    mChanges = changes;
}

QString UpdateIncidenceToolJob::invalidArgumentsMessage() const
{
    if (mItemId < 0) {
        return i18n("Incidence id must be a positive integer");
    }
    return i18n("No field to update");
}

void UpdateIncidenceToolJob::startJob()
{
    auto fetchJob = new Akonadi::ItemFetchJob(Akonadi::Item(mItemId), this);
    fetchJob->fetchScope().fetchFullPayload();
    connect(fetchJob, &KJob::result, this, &UpdateIncidenceToolJob::slotItemFetchResult);
    setCurrentJob(fetchJob);
}

void UpdateIncidenceToolJob::slotItemFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Incidence fetch failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemFetchJob *>(job)->items();
    if (items.isEmpty()) {
        finish(i18n("Incidence %1 not found", mItemId), true);
        return;
    }
    Akonadi::Item item = items.at(0);
    const KCalendarCore::Incidence::Ptr incidence = Akonadi::CalendarUtils::incidence(item);
    if (!incidence) {
        finish(i18n("Item %1 is not an event, a to-do or a journal entry", mItemId), true);
        return;
    }
    if (const QString error = applyChanges(incidence); !error.isEmpty()) {
        finish(error, true);
        return;
    }
    item.setPayload<KCalendarCore::Incidence::Ptr>(incidence);

    auto modifyJob = new Akonadi::ItemModifyJob(item, this);
    modifyJob->setProperty("summary", incidence->summary());
    modifyJob->setProperty("incidenceType", static_cast<int>(incidence->type()));
    connect(modifyJob, &KJob::result, this, &UpdateIncidenceToolJob::slotItemModifyResult);
    setCurrentJob(modifyJob);
}

void UpdateIncidenceToolJob::slotItemModifyResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Incidence modification failed: %1"))) {
        return;
    }
    const QString summary = job->property("summary").toString();
    const QString itemId = QString::number(mItemId);
    switch (job->property("incidenceType").toInt()) {
    case KCalendarCore::IncidenceBase::TypeEvent:
        finish(i18n("Event \"%1\" updated (item id: %2)", summary, itemId));
        break;
    case KCalendarCore::IncidenceBase::TypeTodo:
        finish(i18n("To-do \"%1\" updated (item id: %2)", summary, itemId));
        break;
    case KCalendarCore::IncidenceBase::TypeJournal:
        finish(i18n("Journal entry \"%1\" updated (item id: %2)", summary, itemId));
        break;
    default:
        finish(i18n("\"%1\" updated (item id: %2)", summary, itemId));
        break;
    }
}

QString UpdateIncidenceToolJob::applyChanges(const KCalendarCore::Incidence::Ptr &incidence) const
{
    const KCalendarCore::IncidenceBase::IncidenceType type = incidence->type();
    if (mChanges.end && type != KCalendarCore::IncidenceBase::TypeEvent) {
        return i18n("Argument end is only valid for events");
    }
    if ((mChanges.due || mChanges.priority || mChanges.completed) && type != KCalendarCore::IncidenceBase::TypeTodo) {
        return i18n("Arguments due, priority and completed are only valid for to-dos");
    }

    if (type == KCalendarCore::IncidenceBase::TypeEvent) {
        if (const QString error = applyEventChanges(incidence); !error.isEmpty()) {
            return error;
        }
    } else if (type == KCalendarCore::IncidenceBase::TypeTodo) {
        if (const QString error = applyTodoChanges(incidence); !error.isEmpty()) {
            return error;
        }
    } else if (mChanges.start) {
        incidence->setDtStart(mChanges.start->dateTime);
        incidence->setAllDay(mChanges.start->allDay);
    }

    if (mChanges.summary) {
        incidence->setSummary(*mChanges.summary);
    }
    if (mChanges.description) {
        incidence->setDescription(*mChanges.description);
    }
    if (mChanges.location) {
        incidence->setLocation(*mChanges.location);
    }
    return {};
}

QString UpdateIncidenceToolJob::applyEventChanges(const KCalendarCore::Incidence::Ptr &incidence) const
{
    if (!mChanges.start && !mChanges.end) {
        return {};
    }
    const auto event = incidence.staticCast<KCalendarCore::Event>();
    const bool allDay = mChanges.start ? mChanges.start->allDay : mChanges.end->allDay;
    if (!mChanges.start && allDay != event->allDay()) {
        return event->allDay() ? i18n("Argument end must be a date for an all-day event") : i18n("Argument end must be a date-time for a timed event");
    }

    const QDateTime start = mChanges.start ? mChanges.start->dateTime : event->dtStart();
    QDateTime end;
    if (mChanges.end) {
        end = mChanges.end->dateTime;
    } else if (allDay != event->allDay()) {
        end = allDay ? start : start.addSecs(defaultDurationSecs);
    } else if (event->hasEndDate()) {
        // Keep the duration when only the start is moved
        end = allDay ? start.addDays(event->dtStart().date().daysTo(event->dtEnd().date())) : start.addSecs(event->dtStart().secsTo(event->dtEnd()));
    }
    if (end.isValid() && end < start) {
        return i18n("Argument end must not be before start");
    }

    event->setDtStart(start);
    if (end.isValid()) {
        event->setDtEnd(end);
    }
    event->setAllDay(allDay);
    return {};
}

QString UpdateIncidenceToolJob::applyTodoChanges(const KCalendarCore::Incidence::Ptr &incidence) const
{
    const auto todo = incidence.staticCast<KCalendarCore::Todo>();
    if (mChanges.start || mChanges.due) {
        const bool clearDue = mChanges.due && !mChanges.due->dateTime.isValid();
        const QDateTime start = mChanges.start ? mChanges.start->dateTime : todo->dtStart();
        const QDateTime due = mChanges.due ? mChanges.due->dateTime : todo->dtDue(true);
        bool allDay = todo->allDay();
        if (mChanges.due && !clearDue) {
            allDay = mChanges.due->allDay;
        } else if (mChanges.start) {
            allDay = mChanges.start->allDay;
        }
        // KCalendarCore stores a single all-day flag for both dates
        const bool startMismatch = start.isValid() && !mChanges.start && todo->hasStartDate() && todo->allDay() != allDay;
        const bool dueMismatch = due.isValid() && !mChanges.due && todo->hasDueDate() && todo->allDay() != allDay;
        if (startMismatch || dueMismatch) {
            return i18n("Start and due dates of a to-do must both be dates or both be date-times");
        }
        if (start.isValid() && due.isValid() && due < start) {
            return i18n("Due date must not be before start");
        }

        if (mChanges.start) {
            todo->setDtStart(start);
        }
        if (mChanges.due) {
            todo->setDtDue(clearDue ? QDateTime() : due, true);
        }
        todo->setAllDay(allDay);
    }
    if (mChanges.priority) {
        todo->setPriority(*mChanges.priority);
    }
    if (mChanges.completed) {
        todo->setCompleted(*mChanges.completed);
    }
    return {};
}

#include "moc_updateincidencetooljob.cpp"

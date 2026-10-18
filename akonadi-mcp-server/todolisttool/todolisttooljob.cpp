/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "todolisttooljob.h"
#include "calendarcommon/calendartoolutils.h"
#include <KCalendarCore/Todo>
#include <KLocalizedString>
#include <algorithm>

using namespace Qt::Literals::StringLiterals;

namespace
{
constexpr int maximumEntries = 200;

[[nodiscard]] bool lessThan(const KCalendarCore::Todo::Ptr &left, const KCalendarCore::Todo::Ptr &right)
{
    // To-dos with a due date first, sorted by due date, then by priority (1 is the highest, 0 undefined)
    if (left->hasDueDate() != right->hasDueDate()) {
        return left->hasDueDate();
    }
    if (left->hasDueDate() && left->dtDue() != right->dtDue()) {
        return left->dtDue() < right->dtDue();
    }
    const int leftPriority = left->priority() == 0 ? 10 : left->priority();
    const int rightPriority = right->priority() == 0 ? 10 : right->priority();
    return leftPriority < rightPriority;
}

[[nodiscard]] QString todoEntry(const KCalendarCore::Todo::Ptr &todo)
{
    QString entry = (todo->isCompleted() ? u"[x] "_s : u"[ ] "_s) + todo->summary();
    QStringList details;
    if (todo->hasDueDate()) {
        const QString due = todo->allDay() ? todo->dtDue().date().toString(Qt::ISODate) : CalendarToolUtils::formatDateTime(todo->dtDue());
        details.append(u"due "_s + due);
        if (todo->isOverdue()) {
            details.append(u"overdue"_s);
        }
    }
    if (todo->priority() > 0) {
        details.append(u"priority %1"_s.arg(todo->priority()));
    }
    if (!todo->isCompleted() && todo->percentComplete() > 0) {
        details.append(u"%1% done"_s.arg(todo->percentComplete()));
    }
    if (const Akonadi::Item::Id id = CalendarToolUtils::itemId(todo); id >= 0) {
        details.append(u"id: %1"_s.arg(id));
    }
    if (!details.isEmpty()) {
        entry += u" ("_s + details.join(u", "_s) + u')';
    }
    return entry;
}
}

TodoListToolJob::TodoListToolJob(QObject *parent)
    : CalendarToolJobBase{parent}
{
}

TodoListToolJob::~TodoListToolJob() = default;

void TodoListToolJob::setIncludeCompleted(bool includeCompleted)
{
    mIncludeCompleted = includeCompleted;
}

void TodoListToolJob::setDueWithinDays(int days)
{
    mDueWithinDays = days;
}

QStringList TodoListToolJob::mimeTypes() const
{
    return {KCalendarCore::Todo::todoMimeType()};
}

QString TodoListToolJob::generateResult(const KCalendarCore::Calendar::Ptr &calendar) const
{
    const QDate lastDueDate = QDate::currentDate().addDays(mDueWithinDays);
    KCalendarCore::Todo::List todos = calendar->rawTodos();
    const auto removed = std::ranges::remove_if(todos, [this, lastDueDate](const KCalendarCore::Todo::Ptr &todo) {
        if (!mIncludeCompleted && todo->isCompleted()) {
            return true;
        }
        if (mDueWithinDays > 0) {
            return !todo->hasDueDate() || todo->dtDue().toLocalTime().date() > lastDueDate;
        }
        return false;
    });
    todos.erase(removed.begin(), removed.end());
    if (todos.isEmpty()) {
        return i18n("No to-do found");
    }
    std::ranges::sort(todos, lessThan);

    QStringList entries;
    entries.reserve(std::min<qsizetype>(todos.count(), maximumEntries) + 1);
    for (const KCalendarCore::Todo::Ptr &todo : std::as_const(todos)) {
        if (entries.count() == maximumEntries) {
            entries.append(u"... and %1 more to-dos"_s.arg(todos.count() - maximumEntries));
            break;
        }
        entries.append(todoEntry(todo));
    }
    return entries.join(u'\n');
}

/* SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>
   SPDX-FileContributor: Sérgio Martins <sergio.martins@kdab.com>

   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/
#include "memorycalendarmemento.h"
#include "text_calendar_debug.h"
#include <Akonadi/ETMCalendar>
#include <Akonadi/FetchJobCalendar>
#include <CalendarSupport/CalendarSingleton>

using namespace MessageViewer;
using namespace Akonadi;

MemoryCalendarMemento::MemoryCalendarMemento()
    : QObject(nullptr)
{
    Akonadi::ETMCalendar::Ptr etmCalendar = CalendarSupport::calendarSingleton(/*createIfNull=*/false);
    if (etmCalendar && !etmCalendar->isLoading()) {
        // Good, either korganizer or kontact summary view are already running, so reuse ETM to save memory
        mCalendar = etmCalendar;
        QMetaObject::invokeMethod(this, "finalize", Qt::QueuedConnection);
    } else {
        FetchJobCalendar::Ptr calendar = FetchJobCalendar::Ptr(new FetchJobCalendar(this));
        mCalendar = calendar;
        connect(calendar.data(), &FetchJobCalendar::loadFinished, this, &MemoryCalendarMemento::slotCalendarLoaded);
    }
}

void MemoryCalendarMemento::slotCalendarLoaded(bool success, const QString &errorMessage)
{
    qCDebug(TEXT_CALENDAR_LOG) << "MemoryCalendarMemento::slotCalendarLoaded: " << success;
    if (!success) {
        qCWarning(TEXT_CALENDAR_LOG) << "Unable to fetch incidences:" << errorMessage;
    }

    finalize();
}

void MemoryCalendarMemento::finalize()
{
    mFinished = true;
    Q_EMIT update(MimeTreeParser::Delayed);
}

bool MemoryCalendarMemento::finished() const
{
    return mFinished;
}

Akonadi::CalendarBase::Ptr MemoryCalendarMemento::calendar() const
{
    Q_ASSERT(mFinished);
    return mCalendar;
}

void MemoryCalendarMemento::detach()
{
    disconnect(this, &MemoryCalendarMemento::update, nullptr, nullptr);
}

#include "moc_memorycalendarmemento.cpp"

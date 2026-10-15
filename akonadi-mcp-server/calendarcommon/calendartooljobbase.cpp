/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "calendartooljobbase.h"
#include <Akonadi/CalendarUtils>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/RecursiveItemFetchJob>
#include <KCalendarCore/MemoryCalendar>
#include <KJob>
#include <KLocalizedString>
#include <QTimeZone>

CalendarToolJobBase::CalendarToolJobBase(QObject *parent)
    : ToolJobBase{parent}
{
}

CalendarToolJobBase::~CalendarToolJobBase() = default;

void CalendarToolJobBase::startJob()
{
    auto fetchJob = new Akonadi::RecursiveItemFetchJob(Akonadi::Collection::root(), mimeTypes(), this);
    fetchJob->fetchScope().fetchFullPayload();
    connect(fetchJob, &KJob::result, this, &CalendarToolJobBase::slotResult);
    setCurrentJob(fetchJob);
    fetchJob->start();
}

void CalendarToolJobBase::slotResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Calendar fetch failed: %1"))) {
        return;
    }
    const auto calendar = KCalendarCore::MemoryCalendar::Ptr::create(QTimeZone::systemTimeZone());
    const Akonadi::Item::List items = qobject_cast<Akonadi::RecursiveItemFetchJob *>(job)->items();
    for (const Akonadi::Item &item : items) {
        if (const KCalendarCore::Incidence::Ptr incidence = Akonadi::CalendarUtils::incidence(item)) {
            calendar->addIncidence(incidence);
        }
    }
    finish(generateResult(calendar));
}

#include "moc_calendartooljobbase.cpp"

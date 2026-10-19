/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deleteincidencetooljob.h"
#include <Akonadi/CalendarUtils>
#include <Akonadi/ItemDeleteJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <KCalendarCore/Incidence>
#include <KLocalizedString>

DeleteIncidenceToolJob::DeleteIncidenceToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

DeleteIncidenceToolJob::~DeleteIncidenceToolJob() = default;

bool DeleteIncidenceToolJob::canStart() const
{
    return ToolJobBase::canStart() && mItemId >= 0;
}

void DeleteIncidenceToolJob::setItemId(qint64 itemId)
{
    mItemId = itemId;
}

QString DeleteIncidenceToolJob::invalidArgumentsMessage() const
{
    return i18n("Incidence id must be a positive integer");
}

void DeleteIncidenceToolJob::startJob()
{
    // Fetch the item first to make sure that we only delete an incidence
    auto fetchJob = new Akonadi::ItemFetchJob(Akonadi::Item(mItemId), this);
    fetchJob->fetchScope().fetchFullPayload();
    connect(fetchJob, &KJob::result, this, &DeleteIncidenceToolJob::slotItemFetchResult);
    setCurrentJob(fetchJob);
}

void DeleteIncidenceToolJob::slotItemFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Incidence fetch failed: %1"))) {
        return;
    }
    const Akonadi::Item::List items = qobject_cast<Akonadi::ItemFetchJob *>(job)->items();
    if (items.isEmpty()) {
        finish(i18n("Incidence %1 not found", mItemId), true);
        return;
    }
    const Akonadi::Item &item = items.at(0);
    const KCalendarCore::Incidence::Ptr incidence = Akonadi::CalendarUtils::incidence(item);
    if (!incidence) {
        finish(i18n("Item %1 is not an event, a to-do or a journal entry", mItemId), true);
        return;
    }

    auto deleteJob = new Akonadi::ItemDeleteJob(item, this);
    deleteJob->setProperty("summary", incidence->summary());
    deleteJob->setProperty("incidenceType", static_cast<int>(incidence->type()));
    connect(deleteJob, &KJob::result, this, &DeleteIncidenceToolJob::slotItemDeleteResult);
    setCurrentJob(deleteJob);
}

void DeleteIncidenceToolJob::slotItemDeleteResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Incidence deletion failed: %1"))) {
        return;
    }
    const QString summary = job->property("summary").toString();
    const QString itemId = QString::number(mItemId);
    switch (job->property("incidenceType").toInt()) {
    case KCalendarCore::IncidenceBase::TypeEvent:
        finish(i18n("Event \"%1\" deleted (item id: %2)", summary, itemId));
        break;
    case KCalendarCore::IncidenceBase::TypeTodo:
        finish(i18n("To-do \"%1\" deleted (item id: %2)", summary, itemId));
        break;
    case KCalendarCore::IncidenceBase::TypeJournal:
        finish(i18n("Journal entry \"%1\" deleted (item id: %2)", summary, itemId));
        break;
    default:
        finish(i18n("\"%1\" deleted (item id: %2)", summary, itemId));
        break;
    }
}

#include "moc_deleteincidencetooljob.cpp"

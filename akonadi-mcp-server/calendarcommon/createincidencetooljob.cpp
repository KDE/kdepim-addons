/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "createincidencetooljob.h"
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/Item>
#include <Akonadi/ItemCreateJob>
#include <KJob>
#include <KLocalizedString>

CreateIncidenceToolJob::CreateIncidenceToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

CreateIncidenceToolJob::~CreateIncidenceToolJob() = default;

void CreateIncidenceToolJob::setIncidence(const KCalendarCore::Incidence::Ptr &incidence)
{
    mIncidence = incidence;
}

bool CreateIncidenceToolJob::canStart() const
{
    return ToolJobBase::canStart() && mIncidence && !mIncidence->summary().isEmpty();
}

void CreateIncidenceToolJob::setCalendarId(Akonadi::Collection::Id id)
{
    mCalendarId = id;
}

QString CreateIncidenceToolJob::invalidArgumentsMessage() const
{
    return i18n("Summary must be a non-empty string");
}

void CreateIncidenceToolJob::startJob()
{
    if (mCalendarId >= 0) {
        auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection(mCalendarId), Akonadi::CollectionFetchJob::Base, this);
        connect(fetchJob, &KJob::result, this, &CreateIncidenceToolJob::slotCollectionFetchResult);
        setCurrentJob(fetchJob);
    } else {
        auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);
        fetchJob->fetchScope().setContentMimeTypes({mIncidence->mimeType()});
        connect(fetchJob, &KJob::result, this, &CreateIncidenceToolJob::slotCollectionFetchResult);
        setCurrentJob(fetchJob);
    }
}

void CreateIncidenceToolJob::slotCollectionFetchResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Calendar fetch failed: %1"))) {
        return;
    }
    const QString mimeType = mIncidence->mimeType();
    const Akonadi::Collection::List collections = qobject_cast<Akonadi::CollectionFetchJob *>(job)->collections();
    for (const Akonadi::Collection &collection : collections) {
        if (collection.isVirtual() || !collection.contentMimeTypes().contains(mimeType) || !(collection.rights() & Akonadi::Collection::CanCreateItem)) {
            continue;
        }
        createIncidence(collection);
        return;
    }
    if (mCalendarId >= 0) {
        finish(i18n("Calendar %1 does not exist or does not accept new items", mCalendarId), true);
    } else {
        finish(i18n("No writable calendar found"), true);
    }
}

void CreateIncidenceToolJob::createIncidence(const Akonadi::Collection &collection)
{
    Akonadi::Item item;
    item.setMimeType(mIncidence->mimeType());
    item.setPayload<KCalendarCore::Incidence::Ptr>(mIncidence);

    auto createJob = new Akonadi::ItemCreateJob(item, collection, this);
    createJob->setProperty("calendarName", collection.displayName());
    connect(createJob, &KJob::result, this, &CreateIncidenceToolJob::slotItemCreateResult);
    setCurrentJob(createJob);
}

void CreateIncidenceToolJob::slotItemCreateResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Creation failed: %1"))) {
        return;
    }
    const Akonadi::Item item = qobject_cast<Akonadi::ItemCreateJob *>(job)->item();
    const QString calendarName = job->property("calendarName").toString();
    const QString itemId = QString::number(item.id());
    switch (mIncidence->type()) {
    case KCalendarCore::IncidenceBase::TypeEvent:
        finish(i18n("Event \"%1\" created in calendar \"%2\" (item id: %3)", mIncidence->summary(), calendarName, itemId));
        break;
    case KCalendarCore::IncidenceBase::TypeTodo:
        finish(i18n("To-do \"%1\" created in calendar \"%2\" (item id: %3)", mIncidence->summary(), calendarName, itemId));
        break;
    case KCalendarCore::IncidenceBase::TypeJournal:
        finish(i18n("Journal entry \"%1\" created in calendar \"%2\" (item id: %3)", mIncidence->summary(), calendarName, itemId));
        break;
    default:
        finish(i18n("\"%1\" created in calendar \"%2\" (item id: %3)", mIncidence->summary(), calendarName, itemId));
        break;
    }
}

#include "moc_createincidencetooljob.cpp"

/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "listcalendarstooljob.h"
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <KJob>
#include <KLocalizedString>

#include <KCalendarCore/Event>
#include <KCalendarCore/Journal>
#include <KCalendarCore/Todo>
using namespace Qt::Literals::StringLiterals;
namespace
{
const QStringList &calendarMimeTypes()
{
    static const QStringList types{KCalendarCore::Event::eventMimeType(), KCalendarCore::Todo::todoMimeType(), KCalendarCore::Journal::journalMimeType()};
    return types;
}

QString listCalendarType(const QStringList &mimeTypes)
{
    QStringList result;
    for (const QString &t : mimeTypes) {
        if (t == KCalendarCore::Event::eventMimeType()) {
            result += u"events"_s;
        } else if (t == KCalendarCore::Todo::todoMimeType()) {
            result += u"todos"_s;
        } else if (t == KCalendarCore::Journal::journalMimeType()) {
            result += u"journals"_s;
        }
    }
    return u"[%1]"_s.arg(result.join(u", "));
}

}

using namespace Qt::Literals::StringLiterals;

ListCalendarsToolJob::ListCalendarsToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

ListCalendarsToolJob::~ListCalendarsToolJob() = default;

void ListCalendarsToolJob::startJob()
{
    auto fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(), Akonadi::CollectionFetchJob::Recursive, this);
    fetchJob->fetchScope().setContentMimeTypes(calendarMimeTypes());
    connect(fetchJob, &KJob::result, this, &ListCalendarsToolJob::slotResult);
    setCurrentJob(fetchJob);
}

void ListCalendarsToolJob::slotResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Calendar fetch failed: %1"))) {
        return;
    }
    const Akonadi::Collection::List collections = qobject_cast<Akonadi::CollectionFetchJob *>(job)->collections();
    QStringList entries;
    entries.reserve(collections.count());
    for (const Akonadi::Collection &collection : collections) {
        if (collection.isVirtual()) {
            continue;
        }
        const QStringList mimeTypes = collection.contentMimeTypes();
        if (std::none_of(calendarMimeTypes().cbegin(), calendarMimeTypes().cend(), [&mimeTypes](const QString &t) {
                return mimeTypes.contains(t);
            })) {
            continue;
        }
        QString entry = u"%1 (id: %2) %3"_s.arg(collection.displayName(), QString::number(collection.id()), listCalendarType(mimeTypes));
        if (!(collection.rights() & Akonadi::Collection::CanCreateItem)) {
            entry += u" [read-only]";
        }
        entries.append(entry);
    }
    if (entries.isEmpty()) {
        finish(i18n("No calendar found"));
    } else {
        finish(entries.join(u'\n'));
    }
}

#include "moc_listcalendarstooljob.cpp"

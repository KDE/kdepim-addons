/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "akonadipimdatasource.h"
#include "eventmodel.h"
#include "pimeventsplugin_debug.h"
#include "settingschangenotifier.h"

#include <Akonadi/AttributeFactory>
#include <Akonadi/Collection>
#include <Akonadi/CollectionColorAttribute>

#include <QSet>

#include <KCoreConfigSkeleton>
#include <KSharedConfig>

using namespace std::placeholders;

AkonadiPimDataSource::AkonadiPimDataSource(QObject *parent)
    : QObject(parent)
    , mCalendar(new EventModel(this))
{
    Akonadi::AttributeFactory::registerAttribute<Akonadi::CollectionColorAttribute>();

    connect(SettingsChangeNotifier::self(), &SettingsChangeNotifier::settingsChanged, this, &AkonadiPimDataSource::onSettingsChanged);

    onSettingsChanged();

    // Would be nice to have a proper API to read KOrganizer calendar colors...
    const auto korganizerrc = KSharedConfig::openConfig(QStringLiteral("korganizerrc"));
    const auto skel = new KCoreConfigSkeleton(korganizerrc);
    mEventViewsPrefs = EventViews::PrefsPtr(new EventViews::Prefs(skel));
    mEventViewsPrefs->readConfig();
}

AkonadiPimDataSource::~AkonadiPimDataSource() = default;

qint64 AkonadiPimDataSource::akonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const
{
    return mCalendar->item(incidence).id();
}

KCalendarCore::Calendar *AkonadiPimDataSource::calendar() const
{
    return mCalendar;
}

QString AkonadiPimDataSource::calendarColorForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const
{
    const auto &item = mCalendar->item(incidence);
    if (!item.isValid()) {
        return {};
    }

    const auto &col = mCalendar->collection(item.parentCollection().id());
    if (!col.isValid()) {
        return {};
    }

    auto it = mColorCache.find(col.id());
    if (it == mColorCache.end()) {
        if (col.hasAttribute<Akonadi::CollectionColorAttribute>()) {
            const auto attr = col.attribute<Akonadi::CollectionColorAttribute>();
            it = mColorCache.insert(col.id(), attr->color().name());
        } else {
            QColor color = mEventViewsPrefs->resourceColorKnown(QString::number(col.id()));
            if (color.isValid()) {
                it = mColorCache.insert(col.id(), color.name());
            } else {
                it = mColorCache.insert(col.id(), QString());
            }
        }
    }
    return *it;
}

void AkonadiPimDataSource::onSettingsChanged()
{
    QSet<Akonadi::Collection> monitored;
    const auto collections = mCalendar->collections();
    monitored.reserve(collections.count());
    for (const Akonadi::Collection &col : collections) {
        monitored.insert(col);
    }

    const auto config = KSharedConfig::openConfig();
    const auto group = config->group("PIMEventsPlugin");
    const QList<qint64> calendars = group.readEntry(QStringLiteral("calendars"), QList<qint64>());
    QSet<Akonadi::Collection> configured;
    for (const auto colId : calendars) {
        configured.insert(Akonadi::Collection(colId));
    }

    const auto toEnable = configured - monitored;
    std::for_each(toEnable.cbegin(), toEnable.cend(), std::bind(&EventModel::addCalendar, mCalendar, _1));
    const auto toDisable = monitored - configured;
    std::for_each(toDisable.cbegin(), toDisable.cend(), std::bind(&EventModel::removeCalendar, mCalendar, _1));
}

#include "moc_akonadipimdatasource.cpp"

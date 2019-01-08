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

#include "akonadipimdatasource.h"
#include "settingschangenotifier.h"
#include "pimeventsplugin_debug.h"
#include "eventmodel.h"

#include <AkonadiCore/Collection>
#include <AkonadiCore/CollectionColorAttribute>
#include <AkonadiCore/AttributeFactory>

#include <QSet>

#include <KSharedConfig>
#include <KCoreConfigSkeleton>

#include <EventViews/Prefs>

using namespace std::placeholders;

AkonadiPimDataSource::AkonadiPimDataSource(QObject *parent)
    : QObject(parent)
{
    Akonadi::AttributeFactory::registerAttribute<Akonadi::CollectionColorAttribute>();

    connect(SettingsChangeNotifier::self(), &SettingsChangeNotifier::settingsChanged,
            this, &AkonadiPimDataSource::onSettingsChanged);

    mCalendar = new EventModel(this);

    onSettingsChanged();

    // Would be nice to have a proper API to read KOrganizer calendar colors...
    const auto korganizerrc = KSharedConfig::openConfig(QStringLiteral("korganizerrc"));
    const auto skel = new KCoreConfigSkeleton(korganizerrc);
    mEventViewsPrefs = EventViews::PrefsPtr(new EventViews::Prefs(skel));
    mEventViewsPrefs->readConfig();
}

AkonadiPimDataSource::~AkonadiPimDataSource()
{
}

qint64 AkonadiPimDataSource::akonadiIdForIncidence(const KCalCore::Incidence::Ptr &incidence) const
{
    return mCalendar->item(incidence).id();
}

KCalCore::Calendar *AkonadiPimDataSource::calendar() const
{
    return mCalendar;
}

QString AkonadiPimDataSource::calendarColorForIncidence(const KCalCore::Incidence::Ptr &incidence) const
{
    const auto &item = mCalendar->item(incidence);
    if (!item.isValid()) {
        return QString();
    }

    const auto &col = mCalendar->collection(item.parentCollection().id());
    if (!col.isValid()) {
        return QString();
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
    std::for_each(toEnable.cbegin(), toEnable.cend(),
                  std::bind(&EventModel::addCalendar, mCalendar, _1));
    const auto toDisable = monitored - configured;
    std::for_each(toDisable.cbegin(), toDisable.cend(),
                  std::bind(&EventModel::removeCalendar, mCalendar, _1));
}

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

#include <AkonadiCore/ChangeRecorder>
#include <AkonadiCore/ItemFetchScope>
#include <AkonadiCore/EntityDisplayAttribute>
#include <AkonadiCore/CollectionColorAttribute>
#include <AkonadiCore/AttributeFactory>
#include <Akonadi/Calendar/ETMCalendar>

#include <KSharedConfig>
#include <KCoreConfigSkeleton>

#include <EventViews/Prefs>

AkonadiPimDataSource::AkonadiPimDataSource(QObject *parent)
    : QObject(parent)
{
    Akonadi::AttributeFactory::registerAttribute<Akonadi::CollectionColorAttribute>();

    connect(SettingsChangeNotifier::self(), &SettingsChangeNotifier::settingsChanged,
            this, &AkonadiPimDataSource::onSettingsChanged);

    mMonitor = new Akonadi::ChangeRecorder(this);
    mMonitor->setChangeRecordingEnabled(false);
    mMonitor->itemFetchScope().fetchFullPayload(true);
    mMonitor->itemFetchScope().fetchAttribute<Akonadi::EntityDisplayAttribute>();
    mMonitor->itemFetchScope().fetchAttribute<Akonadi::CollectionColorAttribute>();
    onSettingsChanged();

    mCalendar = new Akonadi::ETMCalendar(mMonitor, this);
    // TOOD: Only retrieve PLD:HEAD once it's supported
    mCalendar->setCollectionFilteringEnabled(false);

    // Would be nice to have a proper API to read KOrganizer calendar colors...
    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("korganizerrc"));
    KCoreConfigSkeleton *skel = new KCoreConfigSkeleton(config);
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
    return (*it);
}

void AkonadiPimDataSource::onSettingsChanged()
{
    QSet<Akonadi::Collection> currentCols;
    Q_FOREACH (const Akonadi::Collection &col, mMonitor->collectionsMonitored()) {
        currentCols.insert(col);
    }

    auto config = KSharedConfig::openConfig();
    auto group = config->group("PIMEventsPlugin");
    const QList<qint64> calendars = group.readEntry(QStringLiteral("calendars"), QList<qint64>());
    QSet<Akonadi::Collection> configuredCols;
    Q_FOREACH (qint64 colId, calendars) {
        configuredCols.insert(Akonadi::Collection(colId));
    }

    Q_FOREACH (const Akonadi::Collection &col, (currentCols - configuredCols)) {
        mMonitor->setCollectionMonitored(col, false);
    }
    Q_FOREACH (const Akonadi::Collection &col, (configuredCols - currentCols)) {
        mMonitor->setCollectionMonitored(col, true);
    }

    const bool hasSelectedCols = mMonitor->collectionsMonitored().isEmpty();
    mMonitor->setMimeTypeMonitored(KCalCore::Event::eventMimeType(), hasSelectedCols);
    mMonitor->setMimeTypeMonitored(KCalCore::Todo::todoMimeType(), hasSelectedCols);
}

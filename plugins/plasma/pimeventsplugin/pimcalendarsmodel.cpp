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

#include "pimcalendarsmodel.h"
#include "settingschangenotifier.h"

#include <AkonadiCore/ChangeRecorder>
#include <AkonadiCore/CollectionFetchScope>
#include <AkonadiCore/EntityTreeModel>
#include <AkonadiCore/EntityDisplayAttribute>

#include <KCalCore/Event>
#include <KCalCore/Todo>

#include <KSharedConfig>
#include <KConfigGroup>

PimCalendarsModel::PimCalendarsModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSortRole(Qt::DisplayRole);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSortLocaleAware(true);
    setDynamicSortFilter(true);

    auto cr = new Akonadi::ChangeRecorder(this);
    cr->setMimeTypeMonitored(KCalCore::Event::eventMimeType());
    cr->setMimeTypeMonitored(KCalCore::Todo::todoMimeType());
    cr->setTypeMonitored(Akonadi::Monitor::Collections);
    cr->collectionFetchScope().setListFilter(Akonadi::CollectionFetchScope::Enabled);

    mEtm = new Akonadi::EntityTreeModel(cr);
    mEtm->setItemPopulationStrategy(Akonadi::EntityTreeModel::NoItemPopulation);
    mEtm->setListFilter(Akonadi::CollectionFetchScope::Enabled);
    connect(mEtm, &Akonadi::EntityTreeModel::collectionTreeFetched,
    this, [this]() {
        sort(0, Qt::AscendingOrder);
    });

    setSourceModel(mEtm);

    auto config = KSharedConfig::openConfig();
    auto group = config->group("PIMEventsPlugin");
    mEnabledCalendars = QSet<qint64>::fromList(group.readEntry(QStringLiteral("calendars"), QList<qint64>()));
}

PimCalendarsModel::~PimCalendarsModel()
{
}
QHash<int, QByteArray> PimCalendarsModel::roleNames() const
{
    return { { DataRole, "data" } };
}

QVariant PimCalendarsModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return QSortFilterProxyModel::data(index, role);
    }

    if (role != DataRole) {
        return QVariant();
    }

    const auto &col = QSortFilterProxyModel::data(index, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
    if (!col.isValid()) {
        return QVariant();
    }
    const auto mts = col.contentMimeTypes();
    const bool enabled = mts.contains(KCalCore::Event::eventMimeType()) || mts.contains(KCalCore::Todo::todoMimeType());

    auto attr = col.attribute<Akonadi::EntityDisplayAttribute>();
    const QString icon = attr ? attr->iconName() : QString::null;
    return QVariantMap{ { QStringLiteral("id"), col.id() },
        { QStringLiteral("name"), col.displayName() },
        { QStringLiteral("enabled"), enabled },
        { QStringLiteral("checked"), mEnabledCalendars.contains(col.id()) },
        { QStringLiteral("iconName"), icon } };
}

void PimCalendarsModel::setChecked(qint64 collectionId, bool checked)
{
    bool done = false;
    if (checked) {
        done = !mEnabledCalendars.contains(collectionId);
        mEnabledCalendars.insert(collectionId);
    } else {
        done = mEnabledCalendars.remove(collectionId);
    }
    if (done) {
        const QModelIndex idx = Akonadi::EntityTreeModel::modelIndexForCollection(this, Akonadi::Collection(collectionId));
        Q_EMIT dataChanged(idx, idx);
    }
}

void PimCalendarsModel::saveConfig()
{
    auto config = KSharedConfig::openConfig();
    auto group = config->group("PIMEventsPlugin");
    auto savedList = group.readEntry("calendars", QList<qint64>());
    auto currentList = mEnabledCalendars.toList();
    qSort(savedList);
    qSort(currentList);

    if (currentList != savedList) {
        group.writeEntry("calendars", currentList);
        SettingsChangeNotifier::self()->notifySettingsChanged();
    }
}


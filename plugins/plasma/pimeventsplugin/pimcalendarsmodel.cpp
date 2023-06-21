/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#include "pimcalendarsmodel.h"
#include "settingschangenotifier.h"

#include <Akonadi/CollectionFetchScope>
#include <Akonadi/EntityDisplayAttribute>
#include <Akonadi/EntityTreeModel>
#include <Akonadi/Monitor>

#include <KCalendarCore/Event>
#include <KCalendarCore/Todo>

#include <KConfigGroup>
#include <KSharedConfig>

PimCalendarsModel::PimCalendarsModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSortRole(Qt::DisplayRole);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setSortLocaleAware(true);
    setDynamicSortFilter(true);

    auto cr = new Akonadi::Monitor(this);
    cr->setMimeTypeMonitored(KCalendarCore::Event::eventMimeType());
    cr->setMimeTypeMonitored(KCalendarCore::Todo::todoMimeType());
    cr->setTypeMonitored(Akonadi::Monitor::Collections);
    cr->collectionFetchScope().setListFilter(Akonadi::CollectionFetchScope::Enabled);

    mEtm = new Akonadi::EntityTreeModel(cr, this);
    mEtm->setItemPopulationStrategy(Akonadi::EntityTreeModel::NoItemPopulation);
    mEtm->setListFilter(Akonadi::CollectionFetchScope::Enabled);
    connect(mEtm, &Akonadi::EntityTreeModel::collectionTreeFetched, this, [this]() {
        sort(0, Qt::AscendingOrder);
    });

    setSourceModel(mEtm);

    auto config = KSharedConfig::openConfig();
    auto group = config->group("PIMEventsPlugin");
    const auto enabledCalendarIds = group.readEntry(QStringLiteral("calendars"), QList<qint64>());
    mEnabledCalendars = QSet<qint64>(enabledCalendarIds.begin(), enabledCalendarIds.end());
}

PimCalendarsModel::~PimCalendarsModel() = default;

QHash<int, QByteArray> PimCalendarsModel::roleNames() const
{
    return {{DataRole, "data"}};
}

QVariant PimCalendarsModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return QSortFilterProxyModel::data(index, role);
    }

    if (role != DataRole) {
        return {};
    }

    const auto &col = QSortFilterProxyModel::data(index, Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
    if (!col.isValid()) {
        return {};
    }
    const auto mts = col.contentMimeTypes();
    const bool enabled = mts.contains(KCalendarCore::Event::eventMimeType()) || mts.contains(KCalendarCore::Todo::todoMimeType());

    auto attr = col.attribute<Akonadi::EntityDisplayAttribute>();
    const QString icon = attr ? attr->iconName() : QString();
    return QVariantMap{{QStringLiteral("id"), col.id()},
                       {QStringLiteral("name"), col.displayName()},
                       {QStringLiteral("enabled"), enabled},
                       {QStringLiteral("checked"), mEnabledCalendars.contains(col.id())},
                       {QStringLiteral("iconName"), icon}};
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
    auto currentList = mEnabledCalendars.values();
    std::sort(savedList.begin(), savedList.end());
    std::sort(currentList.begin(), currentList.end());

    if (currentList != savedList) {
        group.writeEntry("calendars", currentList);
        SettingsChangeNotifier::self()->notifySettingsChanged();
    }
}

#include "moc_pimcalendarsmodel.cpp"

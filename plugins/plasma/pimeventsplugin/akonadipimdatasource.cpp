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
#include <Akonadi/CollectionModifyJob>

#include <QSet>

#include <KCoreConfigSkeleton>
#include <KSharedConfig>
#include <QRandomGenerator>

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

    auto collection = mCalendar->collection(item.parentCollection().id());
    const auto id = collection.id();
    if (collection.hasAttribute<Akonadi::CollectionColorAttribute>()) {
        const auto colorAttr = collection.attribute<Akonadi::CollectionColorAttribute>();
        if (colorAttr && colorAttr->color().isValid()) {
            colorCache[id] = colorAttr->color();
            return colorAttr->color().name();
        }
    }

    KSharedConfig::Ptr config = KSharedConfig::openConfig(QStringLiteral("korganizerrc"));
    KConfigGroup resourcesColorsConfig(config, QStringLiteral("Resources Colors"));
    const QStringList colorKeyList = resourcesColorsConfig.keyList();

    QColor color;
    for (const QString &key : colorKeyList) {
        if (key.toLongLong() == id) {
            color = resourcesColorsConfig.readEntry(key, QColor("blue"));
        }
    }

    if (!color.isValid()) {
        color.setRgb(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256));
        colorCache[id] = color;
    }

    auto colorAttr = collection.attribute<Akonadi::CollectionColorAttribute>(Akonadi::Collection::AddIfMissing);
    colorAttr->setColor(color);

    auto modifyJob = new Akonadi::CollectionModifyJob(collection);
    connect(modifyJob, &Akonadi::CollectionModifyJob::result, this, [](KJob *job) {
        if (job->error()) {
            qWarning() << "Error occurred modifying collection color: " << job->errorString();
        }
    });

    return color.name();
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
    const auto group = config->group(QStringLiteral("PIMEventsPlugin"));
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

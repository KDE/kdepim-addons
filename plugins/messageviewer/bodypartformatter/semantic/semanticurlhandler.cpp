/*
   Copyright (c) 2017 Volker Krause <vkrause@kde.org>

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published by
   the Free Software Foundation; either version 2 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
   License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to the
   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#include "semanticurlhandler.h"
#include "semanticmemento.h"
#include "semantic_debug.h"

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/NodeHelper>

#include <CalendarSupport/CalendarSingleton>

#include <KItinerary/CalendarHandler>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/Flight>
#include <KItinerary/Place>
#include <KItinerary/Reservation>
#include <KItinerary/SortUtil>

#include <KMime/Content>

#include <KCalCore/Event>

#include <KDBusServiceStarter>
#include <KLocalizedString>

#include <QDate>
#include <QDBusInterface>
#include <QDesktopServices>
#include <QIcon>
#include <QMenu>
#include <QUrlQuery>

#include <memory>

using namespace KItinerary;

bool SemanticUrlHandler::handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const
{
    Q_UNUSED(viewerInstance);
    if (path == QLatin1String("semanticAction")) {
        return true;
    }

    if (path.startsWith(QLatin1String("semanticExpand?"))) {
        auto idx = path.midRef(15).toInt();
        auto m = memento(part);
        m->toggleExpanded(idx);
        const auto nodeHelper = part->nodeHelper();
        emit nodeHelper->update(MimeTreeParser::Delayed);
        return true;
    }

    return false;
}

static QString placeName(const QVariant &place)
{
    const auto name = JsonLdDocument::readProperty(place, "name").toString()
                      .replace(QLatin1Char('&'), QLatin1String("&&")); // avoid & being turned into an action accelerator;
    if (!name.isEmpty()) {
        return name;
    }
    // airports with no name, as extracted from IATA BCBP messages
    return JsonLdDocument::readProperty(place, "iataCode").toString();
}

static void addGoToMapAction(QMenu *menu, const QVariant &place)
{
    if (place.isNull()) {
        return;
    }

    const auto geo = JsonLdDocument::readProperty(place, "geo").value<GeoCoordinates>();
    if (geo.isValid()) {
        auto action = menu->addAction(QIcon::fromTheme(QStringLiteral("map-globe")), i18n("Show \'%1\' On Map", placeName(place)));
        // zoom out further from airports, they are larger and you usually want to go further away from them
        const auto zoom = place.userType() == qMetaTypeId<Airport>() ? 12 : 17;
        QObject::connect(action, &QAction::triggered, menu, [geo, zoom]() {
            QUrl url;
            url.setScheme(QStringLiteral("https"));
            url.setHost(QStringLiteral("www.openstreetmap.org"));
            url.setPath(QStringLiteral("/"));
            const QString fragment = QLatin1String("map=") + QString::number(zoom)
                                     + QLatin1Char('/') + QString::number(geo.latitude())
                                     + QLatin1Char('/') + QString::number(geo.longitude());
            url.setFragment(fragment);
            QDesktopServices::openUrl(url);
        });
        return;
    }

    const auto addr = JsonLdDocument::readProperty(place, "address").value<PostalAddress>();
    if (!addr.addressLocality().isEmpty()) {
        auto action = menu->addAction(QIcon::fromTheme(QStringLiteral("map-globe")), i18n("Show \'%1\' On Map", placeName(place)));
        QObject::connect(action, &QAction::triggered, menu, [addr]() {
            QUrl url;
            url.setScheme(QStringLiteral("https"));
            url.setHost(QStringLiteral("www.openstreetmap.org"));
            url.setPath(QStringLiteral("/search"));
            const QString queryString = addr.streetAddress() + QLatin1String(", ")
                                        + addr.postalCode() + QLatin1Char(' ')
                                        + addr.addressLocality() + QLatin1String(", ")
                                        + addr.addressCountry();
            QUrlQuery query;
            query.addQueryItem(QStringLiteral("query"), queryString);
            url.setQuery(query);
            QDesktopServices::openUrl(url);
        });
    }
}

bool SemanticUrlHandler::handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const
{
    Q_UNUSED(part);
    if (path != QLatin1String("semanticAction")) {
        return false;
    }

    const auto m = memento(part);
    if (!m || m->extractedData().isEmpty()) {
        return false;
    }
    const auto date = dateForReservation(m);

    QMenu menu;
    QAction *action = nullptr;
    if (date.isValid()) {
        action = menu.addAction(QIcon::fromTheme(QStringLiteral("view-calendar")), i18n("Show Calendar"));
        QObject::connect(action, &QAction::triggered, this, [this, date](){
            showCalendar(date);
        });
    }

    action = menu.addAction(QIcon::fromTheme(QStringLiteral("appointment-new")), i18n("Add To Calendar"));
    QObject::connect(action, &QAction::triggered, this, [this, m](){
        addToCalendar(m);
    });

    QSet<QString> places;
    for (const auto &r : m->extractedData()) {
        if (r.userType() == qMetaTypeId<LodgingReservation>()) {
            addGoToMapAction(&menu, r.value<LodgingReservation>().reservationFor());
        } else if (r.userType() == qMetaTypeId<FlightReservation>()) {
            const auto flight = r.value<FlightReservation>().reservationFor().value<Flight>();

            auto airport = flight.departureAirport();
            if (!places.contains(airport.iataCode())) {
                addGoToMapAction(&menu, airport);
                places.insert(airport.iataCode());
            }

            airport = flight.arrivalAirport();
            if (!places.contains(airport.iataCode())) {
                addGoToMapAction(&menu, airport);
                places.insert(airport.iataCode());
            }
        } else if (r.userType() == qMetaTypeId<TrainReservation>() || r.userType() == qMetaTypeId<BusReservation>()) {
            const auto trip = JsonLdDocument::readProperty(r, "reservationFor");

            auto station = JsonLdDocument::readProperty(trip, "departureStation");
            auto name = JsonLdDocument::readProperty(station, "name").toString();
            if (!places.contains(name)) {
                addGoToMapAction(&menu, station);
                places.insert(name);
            }

            station = JsonLdDocument::readProperty(trip, "arrivalStation");
            name = JsonLdDocument::readProperty(station, "name").toString();
            if (!places.contains(name)) {
                addGoToMapAction(&menu, station);
                places.insert(name);
            }
        }
    }

    menu.exec(p);
    return true;
}

QString SemanticUrlHandler::statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const
{
    Q_UNUSED(part);
    if (path == QLatin1String("semanticAction")) {
        return i18n("Add reservation to your calendar.");
    }
    return {};
}

SemanticMemento *SemanticUrlHandler::memento(MimeTreeParser::Interface::BodyPart *part) const
{
    const auto node = part->content()->topLevel();
    const auto nodeHelper = part->nodeHelper();
    if (!nodeHelper || !node) {
        return nullptr;
    }
    return dynamic_cast<SemanticMemento *>(nodeHelper->bodyPartMemento(node->topLevel(), "org.kde.messageviewer.semanticData"));
}

QDate SemanticUrlHandler::dateForReservation(SemanticMemento *memento) const
{
    for (const auto &r : memento->extractedData()) {
        const auto dt = SortUtil::startDateTime(r);
        if (dt.isValid()) {
            return dt.date();
        }
    }
    return {};
}

void SemanticUrlHandler::showCalendar(const QDate &date) const
{
    // ensure KOrganizer or Kontact are running
    QString error, dbusService;
    const auto result = KDBusServiceStarter::self()->findServiceFor(QStringLiteral("DBUS/Organizer"), {}, &error, &dbusService) == 0;
    if (!result) {
        qCWarning(SEMANTIC_LOG) << "Failed to start KOrganizer" << error << dbusService;
    }

    // switch to KOrganizer if we are using Kontact
    std::unique_ptr<QDBusInterface> kontactIface(
        new QDBusInterface(QStringLiteral("org.kde.kontact"), QStringLiteral("/KontactInterface"),
                           QStringLiteral("org.kde.kontact.KontactInterface"), QDBusConnection::sessionBus()));
    if (kontactIface->isValid()) {
        kontactIface->call(QStringLiteral("selectPlugin"), QStringLiteral("kontact_korganizerplugin"));
    }

    // select the date of the reservation
    std::unique_ptr<QDBusInterface> korgIface(
        new QDBusInterface(QStringLiteral("org.kde.korganizer"), QStringLiteral("/Calendar"),
                           QStringLiteral("org.kde.Korganizer.Calendar"), QDBusConnection::sessionBus()));
    if (!korgIface->isValid()) {
        qCWarning(SEMANTIC_LOG) << "Calendar interface is not valid! " << korgIface->lastError().message();
        return;
    }
    korgIface->call(QStringLiteral("showEventView"));
    korgIface->call(QStringLiteral("showDate"), date);
}

static void attachPass(const KCalCore::Event::Ptr &event, const QVariant &reservation, SemanticMemento *memento)
{
    if (!JsonLd::canConvert<Reservation>(reservation)) {
        return;
    }

    const auto res = JsonLd::convert<Reservation>(reservation);
    const auto data = memento->rawPassData(res.pkpassPassTypeIdentifier(), res.pkpassSerialNumber());
    if (data.isEmpty()) {
        return;
    }

    event->deleteAttachments(QStringLiteral("application/vnd.apple.pkpass"));
    using namespace KCalCore;
    Attachment::Ptr att(new Attachment(data.toBase64(), QStringLiteral("application/vnd.apple.pkpass")));
    att->setLabel(i18n("Boarding Pass"));
    event->addAttachment(att);
}

void SemanticUrlHandler::addToCalendar(SemanticMemento *memento) const
{
    using namespace KCalCore;

    const auto calendar = CalendarSupport::calendarSingleton(true);
    for (const auto &r : memento->extractedData()) {
        auto event = CalendarHandler::findEvent(calendar, r);
        if (!event) {
            event.reset(new Event);
            CalendarHandler::fillEvent(r, event);
            if (!event->dtStart().isValid() || !event->dtEnd().isValid() || event->summary().isEmpty()) {
                continue;
            }
            attachPass(event, r, memento);
            calendar->addEvent(event);
        } else {
            const auto oldRes = CalendarHandler::reservationForEvent(event);
            const auto mergedRes = JsonLdDocument::apply(oldRes, r);
            event->startUpdates();
            CalendarHandler::fillEvent(mergedRes, event);
            event->endUpdates();
            attachPass(event, r, memento);
            calendar->modifyIncidence(event);
        }
    }
}

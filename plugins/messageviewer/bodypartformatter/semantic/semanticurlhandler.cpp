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

#include <KItinerary/BusTrip>
#include <KItinerary/CalendarHandler>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/Flight>
#include <KItinerary/Organization>
#include <KItinerary/Place>
#include <KItinerary/Reservation>
#include <KItinerary/SortUtil>
#include <KItinerary/TrainTrip>
#include <KItinerary/Taxi>

#include <KMime/Content>

#include <KCalCore/Event>

#include <KDBusServiceStarter>
#include <KLocalizedString>

#include <QDate>
#include <QDBusInterface>
#include <QDesktopServices>
#include <QIcon>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMenu>
#include <QProcess>
#include <QStandardPaths>
#include <QTemporaryFile>
#include <QUrlQuery>
#include <QDBusPendingReply>
#include <QDBusReply>
#include <QVersionNumber>

#include <memory>
#include <type_traits>

using namespace KItinerary;

SemanticUrlHandler::SemanticUrlHandler()
{
    m_appPath = QStandardPaths::findExecutable(QStringLiteral("itinerary"));
}

static bool canAddToCalendar(SemanticMemento *m)
{
    for (const auto &d : m->data()) {
        if (JsonLd::isA<FlightReservation>(d.reservations.at(0))) {
            const auto f = d.reservations.at(0).value<FlightReservation>().reservationFor().value<Flight>();
            if (f.departureTime().isValid() && f.arrivalTime().isValid()) {
                return true;
            }
            continue;
        } else if (SortUtil::startDateTime(d.reservations.at(0)).isValid()) {
            return true;
        }
    }
    return false;
}

bool SemanticUrlHandler::handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const
{
    Q_UNUSED(viewerInstance);
    if (path == QLatin1String("semanticAction")) {
        const auto m = memento(part);
        if (!m || !m->hasData()) {
            qCWarning(SEMANTIC_LOG) << "sementic action: data not found";
            return true;
        }

        handleContextMenuRequest(part, path, QCursor::pos());
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

template<typename T>
static QString placeName(const T &place)
{
    return place.name().replace(QLatin1Char('&'), QLatin1String("&&")); // avoid & being turned into an action accelerator;
}

template<>
QString placeName(const Airport &place)
{
    if (place.name().isEmpty()) {
        return place.iataCode();
    }
    return place.name().replace(QLatin1Char('&'), QLatin1String("&&")); // avoid & being turned into an action accelerator;
}

static void addGoToMapAction(QMenu *menu, const GeoCoordinates &geo, const QString &placeName, int zoom = 17)
{
    if (geo.isValid()) {
        auto action = menu->addAction(QIcon::fromTheme(QStringLiteral("map-symbolic")), i18n("Show \'%1\' On Map", placeName));
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
    }
}

static void addGoToMapAction(QMenu *menu, const PostalAddress &addr, const QString &placeName)
{
    if (!addr.addressLocality().isEmpty()) {
        auto action = menu->addAction(QIcon::fromTheme(QStringLiteral("map-symbolic")), i18n("Show \'%1\' On Map", placeName));
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

template<typename T>
static void addGoToMapAction(QMenu *menu, const T &place)
{
    const auto name = placeName(place);
    // zoom out further from airports, they are larger and you usually want to go further away from them
    addGoToMapAction(menu, place.geo(), name, std::is_same<T, Airport>::value ? 12 : 17);
    if (!place.geo().isValid()) {
        addGoToMapAction(menu, place.address(), name);
    }
}

bool SemanticUrlHandler::handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const
{
    Q_UNUSED(part);
    if (path != QLatin1String("semanticAction")) {
        return false;
    }

    const auto m = memento(part);
    if (!m || !m->hasData()) {
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
    action->setEnabled(canAddToCalendar(m));
    QObject::connect(action, &QAction::triggered, this, [this, m](){
        addToCalendar(m);
    });

    QSet<QString> places;
    for (const auto &d : m->data()) {
        const auto res = d.reservations.at(0); // for multi-traveler reservations all subsequent ones are equal regarding what we are interested here
        if (JsonLd::isA<LodgingReservation>(res)) {
            addGoToMapAction(&menu, res.value<LodgingReservation>().reservationFor().value<LodgingBusiness>());
        } else if (JsonLd::isA<FlightReservation>(res)) {
            const auto flight = res.value<FlightReservation>().reservationFor().value<Flight>();

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
        } else if (JsonLd::isA<TrainReservation>(res)) {
            const auto trip = res.value<TrainReservation>().reservationFor().value<TrainTrip>();
            if (!places.contains(trip.departureStation().name())) {
                addGoToMapAction(&menu, trip.departureStation());
                places.insert(trip.departureStation().name());
            }
            if (!places.contains(trip.arrivalStation().name())) {
                addGoToMapAction(&menu, trip.arrivalStation());
                places.insert(trip.arrivalStation().name());
            }
        } else if (JsonLd::isA<BusReservation>(res)) {
            const auto trip = res.value<BusReservation>().reservationFor().value<BusTrip>();
            if (!places.contains(trip.departureBusStop().name())) {
                addGoToMapAction(&menu, trip.departureBusStop());
                places.insert(trip.departureBusStop().name());
            }
            if (!places.contains(trip.arrivalBusStop().name())) {
                addGoToMapAction(&menu, trip.arrivalBusStop());
                places.insert(trip.arrivalBusStop().name());
            }
        } else if (JsonLd::isA<FoodEstablishmentReservation>(res)) {
            addGoToMapAction(&menu, res.value<FoodEstablishmentReservation>().reservationFor().value<FoodEstablishment>());
        } else if (JsonLd::isA<RentalCarReservation>(res)) {
            const auto pickupLocation = res.value<RentalCarReservation>().pickupLocation();
            if (!places.contains(pickupLocation.name())) {
                addGoToMapAction(&menu, pickupLocation);
                places.insert(pickupLocation.name());
            }
            const auto dropoffLocation = res.value<RentalCarReservation>().dropoffLocation();
            if (!places.contains(dropoffLocation.name())) {
                addGoToMapAction(&menu, dropoffLocation);
                places.insert(dropoffLocation.name());
            }
        } else if (JsonLd::isA<TaxiReservation>(res)) {
            const auto pickupLocation = res.value<TaxiReservation>().pickupLocation();
            if (!places.contains(pickupLocation.name())) {
                addGoToMapAction(&menu, pickupLocation);
                places.insert(pickupLocation.name());
            }
        }
    }

    if (!m_appPath.isEmpty()) {
        menu.addSeparator();
        action = menu.addAction(QIcon::fromTheme(QStringLiteral("map-globe")), i18n("Import into KDE Itinerary"));
        QObject::connect(action, &QAction::triggered, this, [this, part]() {
            openInApp(part);
        });
    }

    QDBusMessage msg = QDBusMessage::createMethodCall(QStringLiteral("org.kde.kdeconnect"), QStringLiteral("/modules/kdeconnect"), QStringLiteral("org.kde.kdeconnect.daemon"), QStringLiteral(
                                                          "devices"));
    msg.setArguments({true, true});
    QDBusPendingReply<QStringList> reply = QDBusConnection::sessionBus().asyncCall(msg);
    reply.waitForFinished();

    if (reply.isValid()) {
        for (const QString &deviceId : reply.value()) {
            QDBusInterface deviceIface(QStringLiteral("org.kde.kdeconnect"), QStringLiteral("/modules/kdeconnect/devices/") + deviceId, QStringLiteral("org.kde.kdeconnect.device"));

            QDBusReply<bool> pluginReply = deviceIface.call(QLatin1String("hasPlugin"), QLatin1String("kdeconnect_share"));

            if (pluginReply.value()) {
                action = menu.addAction(QIcon::fromTheme(QStringLiteral("kdeconnect")), i18n("Send to %1", deviceIface.property("name").toString()));

                QObject::connect(action, &QAction::triggered, this, [this, part, deviceId]() {
                    openWithKDEConnect(part, deviceId);
                });
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
    for (const auto &d : memento->data()) {
        const auto dt = SortUtil::startDateTime(d.reservations.at(0));
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

static void attachPass(const KCalCore::Event::Ptr &event, const QVector<QVariant> &reservations, SemanticMemento *memento)
{
    for (const auto &reservation : reservations) {
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
        att->setLabel(i18n("Boarding Pass")); // TODO add passenger name after string freeze is lifted
        event->addAttachment(att);
    }
}

void SemanticUrlHandler::addToCalendar(SemanticMemento *memento) const
{
    using namespace KCalCore;

    const auto calendar = CalendarSupport::calendarSingleton(true);
    for (const auto &d : memento->data()) {
        auto event = d.event;
        if (!event) {
            event.reset(new Event);
            CalendarHandler::fillEvent(d.reservations, event);
            if (!event->dtStart().isValid() || !event->dtEnd().isValid() || event->summary().isEmpty()) {
                continue;
            }
            attachPass(event, d.reservations, memento);
            calendar->addEvent(event);
        } else {
            event->startUpdates();
            CalendarHandler::fillEvent(d.reservations, event);
            event->endUpdates();
            attachPass(event, d.reservations, memento);
            calendar->modifyIncidence(event);
        }
    }
}

void SemanticUrlHandler::openInApp(MimeTreeParser::Interface::BodyPart *part) const
{
    QTemporaryFile f(QStringLiteral("itinerary.XXXXXX.jsonld"));
    if (!f.open()) {
        qCWarning(SEMANTIC_LOG) << "Failed to open temporary file:" << f.errorString();
        return;
    }

    const auto m = memento(part);
    const auto extractedData = m->data();
    QVector<QVariant> data;
    data.reserve(extractedData.size());
    for (const auto &d : m->data()) {
        data += d.reservations;
    }
    f.write(QJsonDocument(JsonLdDocument::toJson(data)).toJson());
    f.close();
    part->nodeHelper()->addTempFile(f.fileName());
    f.setAutoRemove(false);

    QStringList args(f.fileName());

    // add pkpass attachments
    for (const auto &elem : data) {
        if (!JsonLd::canConvert<Reservation>(elem)) {
            continue;
        }
        const auto res = JsonLd::convert<Reservation>(elem);
        const auto b = m->rawPassData(res.pkpassPassTypeIdentifier(), res.pkpassSerialNumber());
        if (b.isEmpty()) {
            continue;
        }

        QTemporaryFile f(QStringLiteral("itinerary.XXXXXX.pkpass"));
        if (!f.open()) {
            qCWarning(SEMANTIC_LOG) << "Failed to open temporary file:" << f.errorString();
            return;
        }
        f.write(b);
        f.close();
        part->nodeHelper()->addTempFile(f.fileName());
        f.setAutoRemove(false);
        args.push_back(f.fileName());
    }

    QProcess::startDetached(m_appPath, args);
}

void SemanticUrlHandler::openWithKDEConnect(MimeTreeParser::Interface::BodyPart *part, const QString &deviceId) const
{
    QTemporaryFile f(QStringLiteral("itinerary.XXXXXX.jsonld"));
    if (!f.open()) {
        qCWarning(SEMANTIC_LOG) << "Failed to open temporary file:" << f.errorString();
        return;
    }

    const auto m = memento(part);
    const auto extractedData = m->data();
    QVector<QVariant> data;
    data.reserve(extractedData.size());
    for (const auto &d : m->data()) {
        data += d.reservations;
    }
    f.write(QJsonDocument(JsonLdDocument::toJson(data)).toJson());
    f.close();
    part->nodeHelper()->addTempFile(f.fileName());
    f.setAutoRemove(false);


    QDBusInterface remoteApp(QStringLiteral("org.kde.kdeconnect"), QStringLiteral("/MainApplication"), QStringLiteral("org.qtproject.Qt.QCoreApplication"));
    QVersionNumber kdeconnectVersion = QVersionNumber::fromString(remoteApp.property("applicationVersion").toString());

    QString method;
    if(kdeconnectVersion >= QVersionNumber(1, 4, 0)) {
        method = QStringLiteral("openFile");
    } else {
        method = QStringLiteral("shareUrl");
    }

    QDBusMessage msg = QDBusMessage::createMethodCall(QStringLiteral("org.kde.kdeconnect"), QStringLiteral("/modules/kdeconnect/devices/") + deviceId + QStringLiteral("/share"), QStringLiteral(
                                             "org.kde.kdeconnect.device.share"), method);
    msg.setArguments({QUrl::fromLocalFile(f.fileName()).toString()});

    QDBusConnection::sessionBus().send(msg);

    // add pkpass attachments
    for (const auto &elem : data) {
        if (!JsonLd::canConvert<Reservation>(elem)) {
            continue;
        }
        const auto res = JsonLd::convert<Reservation>(elem);
        const auto b = m->rawPassData(res.pkpassPassTypeIdentifier(), res.pkpassSerialNumber());
        if (b.isEmpty()) {
            continue;
        }

        QTemporaryFile f(QStringLiteral("itinerary.XXXXXX.pkpass"));
        if (!f.open()) {
            qCWarning(SEMANTIC_LOG) << "Failed to open temporary file:" << f.errorString();
            return;
        }
        f.write(b);
        f.close();
        part->nodeHelper()->addTempFile(f.fileName());
        f.setAutoRemove(false);
        msg.setArguments({QUrl::fromLocalFile(f.fileName()).toString()});

        QDBusConnection::sessionBus().send(msg);
    }
}

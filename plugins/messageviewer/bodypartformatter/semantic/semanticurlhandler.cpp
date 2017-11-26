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
#include "datatypes.h"
#include "jsonlddocument.h"
#include "semanticmemento.h"
#include "semantic_debug.h"

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/NodeHelper>

#include <CalendarSupport/CalendarSingleton>

#include <KMime/Content>

#include <KDBusServiceStarter>
#include <KLocalizedString>

#include <QDate>
#include <QDBusInterface>
#include <QDesktopServices>
#include <QIcon>
#include <QMenu>
#include <QMetaProperty>
#include <QUrlQuery>

#include <memory>

SemanticUrlHandler::SemanticUrlHandler() = default;
SemanticUrlHandler::~SemanticUrlHandler() = default;

bool SemanticUrlHandler::handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const
{
    Q_UNUSED(viewerInstance);
    Q_UNUSED(part);
    return path == QLatin1String("semanticAction");
}

bool SemanticUrlHandler::handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const
{
    Q_UNUSED(part);
    if (path != QLatin1String("semanticAction")) {
        return false;
    }

    const auto m = memento(part);
    if (!m || m->isEmpty()) {
        return false;
    }
    const auto date = dateForReservation(m);

    QMenu menu;
    QAction *action;
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

    for (const auto &r : m->data()) {
        if (r.userType() == qMetaTypeId<LodgingReservation>()) {
            const auto hotel = JsonLdDocument::readProperty(r, "reservationFor");
            const auto addr = JsonLdDocument::readProperty(hotel, "address");
            action = menu.addAction(QIcon::fromTheme(QStringLiteral("map-globe")), i18n("Show %1 On Map", JsonLdDocument::readProperty(hotel, "name").toString()));
            QObject::connect(action, &QAction::triggered, this, [addr]() {
                QUrl url;
                url.setScheme(QStringLiteral("https"));
                url.setHost(QStringLiteral("www.openstreetmap.org"));
                url.setPath(QStringLiteral("/search"));
                const QString queryString = JsonLdDocument::readProperty(addr, "streetAddress").toString() + QLatin1String(", ")
                    + JsonLdDocument::readProperty(addr, "postalCode").toString() + QLatin1Char(' ')
                    + JsonLdDocument::readProperty(addr, "addressLocality").toString() + QLatin1String(", ")
                    + JsonLdDocument::readProperty(addr, "addressCountry").toString();
                QUrlQuery query;
                query.addQueryItem(QStringLiteral("query"), queryString);
                url.setQuery(query);
                QDesktopServices::openUrl(url);
            });
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
    for (const auto &r : memento->data()) {
        if (r.userType() == qMetaTypeId<FlightReservation>()) {
            const auto v = JsonLdDocument::readProperty(r, "reservationFor");
            const auto d = JsonLdDocument::readProperty(v, "departureTime").toDate();
            if (d.isValid()) {
                return d;
            }
        } else if (r.userType() == qMetaTypeId<LodgingReservation>()) {
            const auto d = JsonLdDocument::readProperty(r, "checkinDate").toDate();
            if (d.isValid()) {
                return d;
            }
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

KCalCore::Event::Ptr SemanticUrlHandler::eventForReservation(const QVariant &reservation) const
{
    if (reservation.userType() == qMetaTypeId<FlightReservation>()) {
        return eventForFlightReservation(reservation);
    } else if (reservation.userType() == qMetaTypeId<LodgingReservation>()) {
        return eventForLodgingReservation(reservation);
    }
    return {};
}

KCalCore::Event::Ptr SemanticUrlHandler::eventForFlightReservation(const QVariant &reservation) const
{
    using namespace KCalCore;

    const auto flight = JsonLdDocument::readProperty(reservation, "reservationFor");
    const auto airline = JsonLdDocument::readProperty(flight, "airline");
    const auto depPort = JsonLdDocument::readProperty(flight, "departureAirport");
    const auto arrPort = JsonLdDocument::readProperty(flight, "arrivalAirport");
    if (flight.isNull() || airline.isNull() || depPort.isNull() || arrPort.isNull()) {
        return {};
    }

    Event::Ptr event(new Event);
    event->setSummary(i18n("Flight %1 %2 from %3 to %4",
        JsonLdDocument::readProperty(airline, "iataCode").toString(),
        JsonLdDocument::readProperty(flight, "flightNumber").toString(),
        JsonLdDocument::readProperty(depPort, "iataCode").toString(),
        JsonLdDocument::readProperty(arrPort, "iataCode").toString()
    ));
    event->setLocation(JsonLdDocument::readProperty(depPort, "name").toString());
    event->setDtStart(JsonLdDocument::readProperty(flight, "departureTime").toDateTime());
    event->setDtEnd(JsonLdDocument::readProperty(flight, "arrivalTime").toDateTime());
    event->setAllDay(false);
    event->setDescription(i18n("Booking reference: %1",
        JsonLdDocument::readProperty(reservation, "reservationNumber").toString()
    ));
    return event;
}

KCalCore::Event::Ptr SemanticUrlHandler::eventForLodgingReservation(const QVariant &reservation) const
{
    using namespace KCalCore;

    const auto lodgingBusiness = JsonLdDocument::readProperty(reservation, "reservationFor");
    const auto address = JsonLdDocument::readProperty(lodgingBusiness, "address");
    if (lodgingBusiness.isNull() || address.isNull()) {
        return {};
    }

    Event::Ptr event(new Event);
    event->setSummary(i18n("Hotel reservation: %1",
        JsonLdDocument::readProperty(lodgingBusiness, "name").toString()
    ));
    event->setLocation(i18n("%1, %2 %3, %4",
        JsonLdDocument::readProperty(address, "streetAddress").toString(),
        JsonLdDocument::readProperty(address, "postalCode").toString(),
        JsonLdDocument::readProperty(address, "addressLocality").toString(),
        JsonLdDocument::readProperty(address, "addressCountry").toString()
    ));
    event->setDtStart(QDateTime(JsonLdDocument::readProperty(reservation, "checkinDate").toDate(), QTime()));
    event->setDtEnd(QDateTime(JsonLdDocument::readProperty(reservation, "checkoutDate").toDate(), QTime(23, 59, 59)));
    event->setAllDay(true);
    event->setDescription(i18n("Booking reference: %1",
        JsonLdDocument::readProperty(reservation, "reservationNumber").toString()
    ));
    event->setTransparency(Event::Transparent);
    return event;
}

void SemanticUrlHandler::addToCalendar(SemanticMemento *memento) const
{
    auto calendar = CalendarSupport::calendarSingleton(true);
    for (const auto &r : memento->data()) {
        const auto event = eventForReservation(r);
        if (!event) {
            continue;
        }
        calendar->addEvent(event);
    }
}

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

#include "itineraryurlhandler.h"
#include "itinerarymemento.h"
#include "itinerary_debug.h"

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/NodeHelper>

#include <CalendarSupport/CalendarSingleton>

#include <KItinerary/BusTrip>
#include <KItinerary/CalendarHandler>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/File>
#include <KItinerary/Flight>
#include <KItinerary/LocationUtil>
#include <KItinerary/Organization>
#include <KItinerary/Place>
#include <KItinerary/Reservation>
#include <KItinerary/SortUtil>
#include <KItinerary/TrainTrip>
#include <KItinerary/Taxi>
#include <KItinerary/Event>

#include <KMime/Content>

#include <KCalendarCore/Event>

#include <KontactInterface/PimUniqueApplication>
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

ItineraryUrlHandler::ItineraryUrlHandler()
{
    m_appPath = QStandardPaths::findExecutable(QStringLiteral("itinerary"));
}

QString ItineraryUrlHandler::name() const
{
    return QString::fromUtf8(staticMetaObject.className());
}

static bool canAddToCalendar(ItineraryMemento *m)
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

bool ItineraryUrlHandler::handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const
{
    Q_UNUSED(viewerInstance);
    if (path == QLatin1String("semanticAction")) {
        const auto m = memento(part);
        if (!m || !m->hasData()) {
            qCWarning(ITINERARY_LOG) << "sementic action: data not found";
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

static QString escapePlaceName(const QString &name)
{
    return QString(name).replace(QLatin1Char('&'), QLatin1String("&&")); // avoid & being turned into an action accelerator;
}

static void addGoToMapAction(QMenu *menu, const GeoCoordinates &geo, const QString &placeName, int zoom = 17)
{
    if (geo.isValid()) {
        auto action = menu->addAction(QIcon::fromTheme(QStringLiteral("map-symbolic")), i18n("Show \'%1\' On Map", escapePlaceName(placeName)));
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
        auto action = menu->addAction(QIcon::fromTheme(QStringLiteral("map-symbolic")), i18n("Show \'%1\' On Map", escapePlaceName(placeName)));
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

static void addGoToMapAction(QMenu *menu, const QVariant &place, QSet<QString> &places)
{
    const auto name = LocationUtil::name(place);
    if (places.contains(name)) {
        return;
    }
    places.insert(name);

    const auto geo = LocationUtil::geo(place);
    const auto zoom = JsonLd::isA<Airport>(place) ? 12 : 17;
    if (geo.isValid()) {
        addGoToMapAction(menu, geo, name, zoom);
    } else {
        addGoToMapAction(menu, LocationUtil::address(place), name);
    }
}

bool ItineraryUrlHandler::handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const
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
        if (LocationUtil::isLocationChange(res)) {
            const auto dep = LocationUtil::departureLocation(res);
            addGoToMapAction(&menu, dep, places);
            const auto arr = LocationUtil::arrivalLocation(res);
            addGoToMapAction(&menu, arr, places);
        } else {
            const auto loc = LocationUtil::location(res);
            addGoToMapAction(&menu, loc, places);
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

            QDBusReply<bool> pluginReply = deviceIface.call(QStringLiteral("hasPlugin"), QLatin1String("kdeconnect_share"));

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

QString ItineraryUrlHandler::statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const
{
    Q_UNUSED(part);
    if (path == QLatin1String("semanticAction")) {
        return i18n("Add reservation to your calendar.");
    }
    return {};
}

ItineraryMemento *ItineraryUrlHandler::memento(MimeTreeParser::Interface::BodyPart *part) const
{
    const auto node = part->content()->topLevel();
    const auto nodeHelper = part->nodeHelper();
    if (!nodeHelper || !node) {
        return nullptr;
    }
    return dynamic_cast<ItineraryMemento *>(nodeHelper->bodyPartMemento(node->topLevel(), "org.kde.messageviewer.semanticData"));
}

QDate ItineraryUrlHandler::dateForReservation(ItineraryMemento *memento) const
{
    for (const auto &d : memento->data()) {
        const auto dt = SortUtil::startDateTime(d.reservations.at(0));
        if (dt.isValid()) {
            return dt.date();
        }
    }
    return {};
}

void ItineraryUrlHandler::showCalendar(const QDate &date) const
{
    // ensure KOrganizer or Kontact are running
    if (KontactInterface::PimUniqueApplication::activateApplication(QLatin1String("korganizer"))) {

        // select the date of the reservation
        QDBusInterface korgIface(QStringLiteral("org.kde.korganizer"), QStringLiteral("/Calendar"),
                QStringLiteral("org.kde.Korganizer.Calendar"), QDBusConnection::sessionBus());
        if (!korgIface.isValid()) {
            qCWarning(ITINERARY_LOG) << "Calendar interface is not valid! " << korgIface.lastError().message();
            return;
        }
        korgIface.call(QStringLiteral("showEventView"));
        korgIface.call(QStringLiteral("showDate"), date);
    }
}

static void attachPass(const KCalendarCore::Event::Ptr &event, const QVector<QVariant> &reservations, ItineraryMemento *memento)
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
        using namespace KCalendarCore;
        Attachment att(data.toBase64(), QStringLiteral("application/vnd.apple.pkpass"));
        att.setLabel(i18n("Boarding Pass")); // TODO add passenger name after string freeze is lifted
        event->addAttachment(att);
    }
}

void ItineraryUrlHandler::addToCalendar(ItineraryMemento *memento) const
{
    using namespace KCalendarCore;

    const auto calendar = CalendarSupport::calendarSingleton(true);
    for (const auto &d : memento->data()) {
        auto event = d.event;
        if (!event) {
            event.reset(new KCalendarCore::Event);
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

void ItineraryUrlHandler::openInApp(MimeTreeParser::Interface::BodyPart *part) const
{
    const auto fileName = createItineraryFile(part);
    QProcess::startDetached(m_appPath, {fileName});
}

void ItineraryUrlHandler::openWithKDEConnect(MimeTreeParser::Interface::BodyPart *part, const QString &deviceId) const
{
    const auto fileName = createItineraryFile(part);

    QDBusInterface remoteApp(QStringLiteral("org.kde.kdeconnect"), QStringLiteral("/MainApplication"), QStringLiteral("org.qtproject.Qt.QCoreApplication"));
    QVersionNumber kdeconnectVersion = QVersionNumber::fromString(remoteApp.property("applicationVersion").toString());

    QString method;
    if (kdeconnectVersion >= QVersionNumber(1, 4, 0)) {
        method = QStringLiteral("openFile");
    } else {
        method = QStringLiteral("shareUrl");
    }

    QDBusMessage msg = QDBusMessage::createMethodCall(QStringLiteral("org.kde.kdeconnect"),
        QStringLiteral("/modules/kdeconnect/devices/") + deviceId + QStringLiteral("/share"),
        QStringLiteral("org.kde.kdeconnect.device.share"), method);
    msg.setArguments({QUrl::fromLocalFile(fileName).toString()});

    QDBusConnection::sessionBus().send(msg);
}

QString ItineraryUrlHandler::createItineraryFile(MimeTreeParser::Interface::BodyPart *part) const
{
    QTemporaryFile f(QStringLiteral("XXXXXX.itinerary"));
    if (!f.open()) {
        qCWarning(ITINERARY_LOG) << "Failed to open temporary file:" << f.errorString();
        return {};
    }
    f.close();
    part->nodeHelper()->addTempFile(f.fileName());
    f.setAutoRemove(false);

    KItinerary::File file(f.fileName());
    if (!file.open(KItinerary::File::Write)) {
        qCWarning(ITINERARY_LOG) << "Failed to open itinerary bundle file:" << file.errorString();
        return {};
    }

    const auto m = memento(part);

    // add reservations
    const auto extractedData = m->data();
    for (const auto &d : extractedData) {
        for (const auto &res : d.reservations) {
            file.addReservation(res);
        }
    }

    // add pkpass attachments
    for (const auto &passData : m->passData()) {
        file.addPass(KItinerary::File::passId(passData.passTypeIdentifier, passData.serialNumber), passData.rawData);
    }

    // add documents
    for (const auto &docData : m->documentData()) {
        file.addDocument(docData.docId, docData.docInfo, docData.rawData);
    }

    return f.fileName();
}

/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itineraryurlhandler.h"
#include "itinerarymemento.h"
#include "itinerarykdeconnecthandler.h"
#include "itinerary_debug.h"

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/NodeHelper>

#include <CalendarSupport/CalendarSingleton>

#include <KItinerary/CalendarHandler>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/File>
#include <KItinerary/LocationUtil>
#include <KItinerary/Organization>
#include <KItinerary/Place>
#include <KItinerary/Reservation>
#include <KItinerary/SortUtil>

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

#include <memory>
#include <type_traits>

using namespace KItinerary;

QString ItineraryUrlHandler::m_appPath;

ItineraryUrlHandler::ItineraryUrlHandler()
{
    m_appPath = QStandardPaths::findExecutable(QStringLiteral("itinerary"));
}

QString ItineraryUrlHandler::name() const
{
    return QString::fromUtf8(staticMetaObject.className());
}

void ItineraryUrlHandler::setKDEConnectHandler(ItineraryKDEConnectHandler *kdeConnect)
{
    m_kdeConnect = kdeConnect;
}

bool ItineraryUrlHandler::handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const
{
    Q_UNUSED(viewerInstance);
    const auto m = memento(part);

    if (path.startsWith(QLatin1String("semanticExpand?"))) {
        auto idx = path.midRef(15).toInt();
        m->toggleExpanded(idx);
        const auto nodeHelper = part->nodeHelper();
        Q_EMIT nodeHelper->update(MimeTreeParser::Delayed);
        return true;
    }

    if (path == QLatin1String("showCalendar")) {
        showCalendar(m->startDate());
        return true;
    }

    if (path == QLatin1String("addToCalendar")) {
        addToCalendar(m);
        return true;
    }

    if (path == QLatin1String("import")) {
        openInApp(part);
        return true;
    }

    if (path == QLatin1String("sendToDeviceList")) {
        handleContextMenuRequest(part, path, QCursor::pos());
        return true;
    }

    if (path.startsWith(QLatin1String("sendToDevice-"))) {
        openWithKDEConnect(part, path.mid(13));
        return true;
    }

    return false;
}

bool ItineraryUrlHandler::handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const
{
    Q_UNUSED(part);
    if (path == QLatin1String("showCalendar") || path == QLatin1String("addToCalendar") || path == QLatin1String("import") || path.startsWith(QLatin1String("sendToDevice-"))) {
        // suppress default context menus for our buttons
        return true;
    }

    if (path != QLatin1String("sendToDeviceList")) {
        return false;
    }

    const auto m = memento(part);
    if (!m || !m->hasData()) {
        return false;
    }

    QMenu menu;
    QAction *action = nullptr;
    const auto devices = m_kdeConnect->devices();
    for (const auto &device : devices) {
        action = menu.addAction(QIcon::fromTheme(QStringLiteral("kdeconnect")), i18n("Send to %1", device.name));
        QObject::connect(action, &QAction::triggered, this, [this, part, device]() {
            openWithKDEConnect(part, device.deviceId);
        });
    }

    menu.exec(p);
    return true;
}

QString ItineraryUrlHandler::statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const
{
    Q_UNUSED(part);
    if (path == QLatin1String("showCalendar")) {
        return i18n("Show calendar at the time of this reservation.");
    }
    if (path == QLatin1String("addToCalendar")) {
        return i18n("Add reservation to your calendar.");
    }
    if (path == QLatin1String("import")) {
        return i18n("Import reservation into KDE Itinerary.");
    }
    if (path.startsWith(QLatin1String("sendToDevice"))) {
        return i18n("Send this reservation to a device using KDE Connect.");
    }
    return {};
}

bool ItineraryUrlHandler::hasItineraryApp()
{
    return !m_appPath.isEmpty();
}

ItineraryMemento *ItineraryUrlHandler::memento(MimeTreeParser::Interface::BodyPart *part) const
{
    const auto node = part->content()->topLevel();
    const auto nodeHelper = part->nodeHelper();
    if (!nodeHelper || !node) {
        return nullptr;
    }
    return dynamic_cast<ItineraryMemento *>(nodeHelper->bodyPartMemento(node->topLevel(), ItineraryMemento::identifier()));
}

void ItineraryUrlHandler::showCalendar(QDate date) const
{
    // ensure KOrganizer or Kontact are running
    if (KontactInterface::PimUniqueApplication::activateApplication(QStringLiteral("korganizer"))) {
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
    const auto datas = memento->data();
    for (const auto &d : datas) {
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
    m_kdeConnect->sendToDevice(fileName, deviceId);
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

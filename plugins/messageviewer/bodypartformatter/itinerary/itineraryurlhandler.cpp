/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itineraryurlhandler.h"
#include "itinerary_debug.h"
#include "itinerarykdeconnecthandler.h"
#include "itinerarymemento.h"

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/NodeHelper>

#include <CalendarSupport/CalendarSingleton>

#include <KItinerary/CalendarHandler>
#include <KItinerary/File>
#include <KItinerary/Reservation>

#include <KCalendarCore/Event>

#include <KIO/ApplicationLauncherJob>
#include <KLocalizedString>
#include <KService>

#include <QDBusInterface>
#include <QDate>
#include <QIcon>
#include <QMenu>
#include <QStandardPaths>
#include <QTemporaryFile>

#include <memory>
#include <type_traits>

using namespace KItinerary;

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
    Q_UNUSED(viewerInstance)
    const auto m = memento(part);

    if (path.startsWith(QLatin1String("semanticExpand?"))) {
        auto idx = QStringView(path).mid(15).toInt();
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
    Q_UNUSED(part)
    if (path == QLatin1String("showCalendar") || path == QLatin1String("addToCalendar") || path == QLatin1String("import")
        || path.startsWith(QLatin1String("sendToDevice-"))) {
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
    Q_UNUSED(part)
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
    return KService::serviceByDesktopName(QStringLiteral("org.kde.itinerary"));
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
    // Start or activate KOrganizer. When Kontact is running it will switch to KOrganizer view
    const auto korgaService = KService::serviceByDesktopName(QStringLiteral("org.kde.korganizer"));

    if (!korgaService) {
        qCWarning(ITINERARY_LOG) << "Could not find KOrganizer";
        return;
    }

    // Open or activate KOrganizer. This will also activate Kontact if running
    auto job = new KIO::ApplicationLauncherJob(korgaService);

    connect(job, &KJob::finished, this, [date](KJob *job) {
        if (job->error()) {
            qCWarning(ITINERARY_LOG) << "failed to run korganizer" << job->errorString();
            return;
        }

        // select the date of the reservation
        QDBusInterface korgIface(QStringLiteral("org.kde.korganizer"),
                                 QStringLiteral("/Calendar"),
                                 QStringLiteral("org.kde.Korganizer.Calendar"),
                                 QDBusConnection::sessionBus());
        if (!korgIface.isValid()) {
            qCWarning(ITINERARY_LOG) << "Calendar interface is not valid! " << korgIface.lastError().message();
            return;
        }
        korgIface.call(QStringLiteral("showEventView"));
        korgIface.call(QStringLiteral("showDate"), date);
    });

    job->start();
}

static void attachPass(const KCalendarCore::Event::Ptr &event, const QList<QVariant> &reservations, ItineraryMemento *memento)
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
        att.setLabel(JsonLd::canConvert<FlightReservation>(reservation) ? i18n("Boarding Pass")
                                                                        : i18n("Ticket")); // TODO add passenger name after string freeze is lifted
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
    auto job = new KIO::ApplicationLauncherJob(KService::serviceByDesktopName(QStringLiteral("org.kde.itinerary")));
    job->setUrls({QUrl::fromLocalFile(fileName)});
    job->start();
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

#include "moc_itineraryurlhandler.cpp"

/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itineraryrenderer.h"
#include "itinerary_debug.h"
#include "itinerarykdeconnecthandler.h"
#include "itinerarymemento.h"
#include "itineraryurlhandler.h"

#include <MessageViewer/HtmlWriter>
#include <MessageViewer/IconNameCache>
#include <MessageViewer/MessagePartRendererManager>

#include <GrantleeTheme/GrantleeKi18nLocalizer>
#include <GrantleeTheme/GrantleeThemeEngine>

#include <KItinerary/Action>
#include <KItinerary/Brand>
#include <KItinerary/BusTrip>
#include <KItinerary/Event>
#include <KItinerary/Flight>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/MergeUtil>
#include <KItinerary/Organization>
#include <KItinerary/Person>
#include <KItinerary/Place>
#include <KItinerary/RentalCar>
#include <KItinerary/Reservation>
#include <KItinerary/Ticket>
#include <KItinerary/TrainTrip>

#include <KColorScheme>

#include <grantlee/engine.h>
#include <grantlee/metatype.h>
#include <grantlee/template.h>

#include <prison/Prison>

#include <QGuiApplication>
#include <QMetaProperty>
#include <QPalette>

using namespace KItinerary;

ItineraryRenderer::ItineraryRenderer() = default;

void ItineraryRenderer::setKDEConnectHandler(ItineraryKDEConnectHandler *kdeConnect)
{
    m_kdeConnect = kdeConnect;
}

bool ItineraryRenderer::render(const MimeTreeParser::MessagePartPtr &msgPart,
                               MessageViewer::HtmlWriter *htmlWriter,
                               MessageViewer::RenderContext *context) const
{
    Q_UNUSED(context)
    const auto mpList = msgPart.dynamicCast<MimeTreeParser::MessagePartList>();
    if (!msgPart->isRoot() || !mpList->hasSubParts()) {
        return false;
    }

    const auto node = mpList->subParts().at(0)->content();
    const auto nodeHelper = msgPart->nodeHelper();
    if (!nodeHelper || !node) {
        return false;
    }

    auto memento = dynamic_cast<ItineraryMemento *>(nodeHelper->bodyPartMemento(node->topLevel(), ItineraryMemento::identifier()));
    if (!memento || !memento->hasData()) {
        return false;
    }
    const auto extractedData = memento->data();
    if (extractedData.isEmpty()) { // hasData() will not be correct for filtered structured data on the first pass through here...
        return false;
    }

    const auto dir = nodeHelper->createTempDir(QStringLiteral("semantic"));
    auto c = MessageViewer::MessagePartRendererManager::self()->createContext();

    QVariantMap style;
    style.insert(QStringLiteral("expandIcon"),
                 QString(QStringLiteral("file://") + MessageViewer::IconNameCache::instance()->iconPathFromLocal(QStringLiteral("quoteexpand.png"))));
    style.insert(QStringLiteral("collapseIcon"),
                 QString(QStringLiteral("file://") + MessageViewer::IconNameCache::instance()->iconPathFromLocal(QStringLiteral("quotecollapse.png"))));
    style.insert(QStringLiteral("palette"), QGuiApplication::palette());
    style.insert(QStringLiteral("viewScheme"), QVariant::fromValue(KColorScheme(QPalette::Normal, KColorScheme::View)));
    c.insert(QStringLiteral("style"), style);

    const bool testMode = qEnvironmentVariableIsSet("BPF_ITINERARY_TESTMODE"); // ensure deterministic results for unit tests
    QVariantMap actionState;
    actionState.insert(QStringLiteral("canShowCalendar"), memento->startDate().isValid());
    actionState.insert(QStringLiteral("canAddToCalendar"), memento->canAddToCalendar());
    actionState.insert(QStringLiteral("hasItineraryApp"), ItineraryUrlHandler::hasItineraryApp() || testMode);
    if (!testMode) {
        const auto devices = m_kdeConnect->devices();
        actionState.insert(QStringLiteral("canSendToDevice"), !devices.isEmpty());
        if (devices.size() == 1) {
            actionState.insert(QStringLiteral("defaultDeviceName"), devices[0].name);
            actionState.insert(QStringLiteral("defaultDeviceId"), devices[0].deviceId);
        }
    }
    c.insert(QStringLiteral("actionState"), actionState);

    // Grantlee can't do indexed map/array lookups, so we need to interleave this here already
    QVariantList elems;
    elems.reserve(extractedData.size());
    int ticketTokenId = 0;
    for (int i = 0; i < extractedData.size(); ++i) {
        QVariantMap data;
        QVariantMap state;
        const auto d = extractedData.at(i);
        state.insert(QStringLiteral("expanded"), d.expanded);
        data.insert(QStringLiteral("state"), state);
        data.insert(QStringLiteral("groupId"), i);

        QVector<QVariant> reservations;
        reservations.reserve(d.reservations.count());
        for (const auto &r : d.reservations) {
            QVariantMap m;
            m.insert(QStringLiteral("reservation"), r);

            // generate ticket barcodes
            const auto ticket = JsonLd::convert<Reservation>(r).reservedTicket().value<Ticket>();
            std::unique_ptr<Prison::AbstractBarcode> barcode;
            switch (ticket.ticketTokenType()) {
            case Ticket::AztecCode:
                barcode.reset(Prison::createBarcode(Prison::Aztec));
                barcode->setData(ticket.ticketTokenData());
                break;
            case Ticket::QRCode:
                barcode.reset(Prison::createBarcode(Prison::QRCode));
                barcode->setData(ticket.ticketTokenData());
                break;
            case Ticket::DataMatrix:
                barcode.reset(Prison::createBarcode(Prison::DataMatrix));
                barcode->setData(ticket.ticketTokenData());
            default:
                break;
            }
            if (barcode) {
                const auto img = barcode->toImage(barcode->preferredSize(qGuiApp->devicePixelRatio()));
                const QString fileName = dir + QLatin1String("/ticketToken") + QString::number(ticketTokenId++) + QLatin1String(".png");
                img.save(fileName);
                m.insert(QStringLiteral("ticketToken"), fileName);
                nodeHelper->addTempFile(fileName);
            }

            reservations.push_back(m);
        }
        data.insert(QStringLiteral("reservations"), QVariant::fromValue(reservations));
        elems.push_back(data);
    }
    c.insert(QStringLiteral("data"), elems);

    auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral("org.kde.messageviewer/itinerary/itinerary.html"));
    const_cast<Grantlee::Engine *>(t->engine())->addDefaultLibrary(QStringLiteral("kitinerary_grantlee_extension"));
    dynamic_cast<GrantleeTheme::Engine *>(const_cast<Grantlee::Engine *>(t->engine()))
        ->localizer()
        ->setApplicationDomain(QByteArrayLiteral("messageviewer_semantic_plugin"));
    Grantlee::OutputStream s(htmlWriter->stream());
    t->render(&s, &c);
    qobject_cast<GrantleeTheme::Engine *>(const_cast<Grantlee::Engine *>(t->engine()))
        ->localizer()
        ->setApplicationDomain(QByteArrayLiteral("libmessageviewer"));
    return false; // yes, false, we want the rest of the email rendered normally after this
}

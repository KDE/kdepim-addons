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

#include "semanticrenderer.h"
#include "semanticmemento.h"
#include "semantic_debug.h"

#include <MessageViewer/IconNameCache>
#include <MessageViewer/HtmlWriter>
#include <MessageViewer/MessagePartRendererManager>

#include <KItinerary/Action>
#include <KItinerary/BusTrip>
#include <KItinerary/Flight>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/Organization>
#include <KItinerary/Place>
#include <KItinerary/Reservation>
#include <KItinerary/Ticket>
#include <KItinerary/TrainTrip>

#include <grantlee/engine.h>
#include <grantlee/metatype.h>
#include <grantlee/template.h>

#include <prison/Prison>

#include <QGuiApplication>
#include <QMetaProperty>
#include <QPalette>

using namespace KItinerary;

// Grantlee has no Q_GADGET support yet
#define GRANTLEE_MAKE_GADGET(Class) \
    GRANTLEE_BEGIN_LOOKUP(Class) \
    const auto idx = Class::staticMetaObject.indexOfProperty(property.toUtf8().constData()); \
    if (idx < 0) { \
        return {};} \
    const auto mp = Class::staticMetaObject.property(idx); \
    return mp.readOnGadget(&object); \
    GRANTLEE_END_LOOKUP

GRANTLEE_MAKE_GADGET(Airport)
GRANTLEE_MAKE_GADGET(Airline)
GRANTLEE_MAKE_GADGET(Flight)
GRANTLEE_MAKE_GADGET(FlightReservation)
GRANTLEE_MAKE_GADGET(LodgingBusiness)
GRANTLEE_MAKE_GADGET(LodgingReservation)
GRANTLEE_MAKE_GADGET(PostalAddress)
GRANTLEE_MAKE_GADGET(Seat)
GRANTLEE_MAKE_GADGET(Ticket)
GRANTLEE_MAKE_GADGET(TrainStation)
GRANTLEE_MAKE_GADGET(TrainTrip)
GRANTLEE_MAKE_GADGET(TrainReservation)
GRANTLEE_MAKE_GADGET(BusStation)
GRANTLEE_MAKE_GADGET(BusTrip)
GRANTLEE_MAKE_GADGET(BusReservation)
GRANTLEE_MAKE_GADGET(CancelAction)
GRANTLEE_MAKE_GADGET(CheckInAction)
GRANTLEE_MAKE_GADGET(DownloadAction)
GRANTLEE_MAKE_GADGET(UpdateAction)
GRANTLEE_MAKE_GADGET(ViewAction)

SemanticRenderer::SemanticRenderer()
{
    Grantlee::registerMetaType<Airport>();
    Grantlee::registerMetaType<Airline>();
    Grantlee::registerMetaType<Flight>();
    Grantlee::registerMetaType<FlightReservation>();
    Grantlee::registerMetaType<LodgingBusiness>();
    Grantlee::registerMetaType<LodgingReservation>();
    Grantlee::registerMetaType<PostalAddress>();
    Grantlee::registerMetaType<Seat>();
    Grantlee::registerMetaType<Ticket>();
    Grantlee::registerMetaType<TrainStation>();
    Grantlee::registerMetaType<TrainTrip>();
    Grantlee::registerMetaType<TrainReservation>();
    Grantlee::registerMetaType<BusStation>();
    Grantlee::registerMetaType<BusTrip>();
    Grantlee::registerMetaType<BusReservation>();
    Grantlee::registerMetaType<CancelAction>();
    Grantlee::registerMetaType<CheckInAction>();
    Grantlee::registerMetaType<DownloadAction>();
    Grantlee::registerMetaType<UpdateAction>();
    Grantlee::registerMetaType<ViewAction>();
}

bool SemanticRenderer::render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const
{
    Q_UNUSED(context);
    const auto mpList = msgPart.dynamicCast<MimeTreeParser::MessagePartList>();
    if (!msgPart->isRoot() || !mpList->hasSubParts()) {
        return false;
    }

    const auto node = mpList->subParts().at(0)->content();
    const auto nodeHelper = msgPart->nodeHelper();
    if (!nodeHelper || !node) {
        return false;
    }

    auto memento = dynamic_cast<SemanticMemento *>(nodeHelper->bodyPartMemento(node->topLevel(), "org.kde.messageviewer.semanticData"));
    if (!memento || !memento->hasData()) {
        return false;
    }

    const auto dir = nodeHelper->createTempDir(QStringLiteral("semantic"));
    auto c = MessageViewer::MessagePartRendererManager::self()->createContext();

    const auto pal = qGuiApp->palette();
    QVariantMap style;
    style.insert(QStringLiteral("frameColor"), pal.link().color().name());
    style.insert(QStringLiteral("expandIcon"), MessageViewer::IconNameCache::instance()->iconPathFromLocal(QStringLiteral("quoteexpand.png")));
    style.insert(QStringLiteral("collapseIcon"), MessageViewer::IconNameCache::instance()->iconPathFromLocal(QStringLiteral("quotecollapse.png")));
    c.insert(QStringLiteral("style"), style);

    // Grantlee can't do indexed map/array lookups, so we need to interleave this here already
    const auto extractedData = memento->data();
    QVariantList elems;
    elems.reserve(extractedData.size());
    for (int i = 0; i < extractedData.size(); ++i) {
        const auto d = extractedData.at(i);
        QVariantMap data;
        data.insert(QStringLiteral("reservation"), d.res);

        QVariantMap state;
        state.insert(QStringLiteral("expanded"), d.expanded);
        data.insert(QStringLiteral("state"), state);

        // generate ticket barcodes
        if (JsonLd::canConvert<Reservation>(d.res)) {
            const auto ticket = JsonLd::convert<Reservation>(d.res).reservedTicket().value<Ticket>();
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
            default:
                break;
            }
            if (barcode) {
                barcode->toImage(barcode->minimumSize()); // minimumSize is only available after we rendered once...
                const auto img = barcode->toImage(barcode->minimumSize());
                const auto fileName = dir + QStringLiteral("/ticketToken") + QString::number(i) + QStringLiteral(".png");
                img.save(fileName);
                data.insert(QStringLiteral("ticketToken"), fileName);
                nodeHelper->addTempFile(fileName);
            }
        }

        elems.push_back(data);
    }
    c.insert(QStringLiteral("data"), elems);

    auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral(":/org.kde.messageviewer/semantic/semantic.html"));
    const_cast<Grantlee::Engine*>(t->engine())->addDefaultLibrary(QStringLiteral("kitinerary_grantlee_extension"));
    Grantlee::OutputStream s(htmlWriter->stream());
    t->render(&s, &c);
    return false; // yes, false, we want the rest of the email rendered normally after this
}

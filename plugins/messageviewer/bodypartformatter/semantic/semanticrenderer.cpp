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
#include "datatypes.h"
#include "jsonlddocument.h"
#include "semanticmemento.h"
#include "semantic_debug.h"

#include <MessageViewer/IconNameCache>
#include <MessageViewer/HtmlWriter>
#include <MessageViewer/MessagePartRendererManager>

#include <grantlee/metatype.h>
#include <grantlee/template.h>

#include <prison/Prison>

#include <QGuiApplication>
#include <QMetaProperty>
#include <QPalette>

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
    if (!memento || memento->isEmpty()) {
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
    QVariantList elems;
    elems.reserve(memento->data().size());
    for (int i = 0; i < memento->data().size(); ++i) {
        const auto res = memento->data().at(i);
        QVariantMap data;
        data.insert(QStringLiteral("reservation"), res);

        QVariantMap state;
        state.insert(QStringLiteral("expanded"), memento->expanded().at(i));
        data.insert(QStringLiteral("state"), state);

        // generate ticket barcodes
        const auto ticket = JsonLdDocument::readProperty(res, "reservedTicket");
        const auto ticketToken = JsonLdDocument::readProperty(ticket, "ticketToken").toString();
        if (ticketToken.startsWith(QLatin1String("azteccode:"), Qt::CaseInsensitive)) {
            std::unique_ptr<Prison::AbstractBarcode> barcode(Prison::createBarcode(Prison::Aztec));
            barcode->setData(ticketToken.mid(10));
            barcode->toImage(barcode->minimumSize()); // minimumSize is only available after we rendered once...
            const auto img = barcode->toImage(barcode->minimumSize());
            const auto fileName = dir + QStringLiteral("/ticketToken") + QString::number(i) + QStringLiteral(".png");
            img.save(fileName);
            data.insert(QStringLiteral("ticketToken"), fileName);
            nodeHelper->addTempFile(fileName);
        }

        elems.push_back(data);
    }
    c.insert(QStringLiteral("data"), elems);

    auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral(":/org.kde.messageviewer/semantic/semantic.html"));
    Grantlee::OutputStream s(htmlWriter->stream());
    t->render(&s, &c);
    return false; // yes, false, we want the rest of the email rendered normally after this
}

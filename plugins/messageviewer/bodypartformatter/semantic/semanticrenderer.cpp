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
#include "semanticmemento.h"
#include "semantic_debug.h"

#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/HtmlWriter>

#include <grantlee/metatype.h>
#include <grantlee/template.h>

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

    qCDebug(SEMANTIC_LOG) << "========================================= Semantic Rendering";
    const auto node = mpList->subParts().at(0)->content();
    const auto nodeHelper = msgPart->nodeHelper();
    if (!nodeHelper || !node) {
        return false;
    }

    auto memento = dynamic_cast<SemanticMemento *>(nodeHelper->bodyPartMemento(node->topLevel(), "org.kde.messageviewer.semanticData"));
    if (!memento || memento->isEmpty()) {
        return false;
    }

    auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
    c.insert(QStringLiteral("data"), QVariant::fromValue(memento->data()));

    const auto pal = qGuiApp->palette();
    QVariantMap style;
    style.insert(QStringLiteral("frameColor"), pal.link().color().name());
    c.insert(QStringLiteral("style"), style);

    auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral(":/org.kde.messageviewer/semantic/semantic.html"));
    Grantlee::OutputStream s(htmlWriter->stream());
    t->render(&s, &c);
    return false; // yes, false, we want the rest of the email rendered normally after this
}

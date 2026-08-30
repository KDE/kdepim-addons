/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itineraryrenderer.h"
#include "itinerarykdeconnecthandler.h"
#include "itinerarymemento.h"
#include "itineraryurlhandler.h"

#include <MessageViewer/HtmlWriter>
#include <MessageViewer/IconNameCache>
#include <MessageViewer/MessagePartRendererManager>

#include <GrantleeTheme/GrantleeKi18nLocalizer>
#include <GrantleeTheme/GrantleeThemeEngine>

#include <KItinerary/Flight>
#include <KItinerary/Reservation>
#include <KItinerary/Ticket>

#include <KColorScheme>
#include <KTextTemplate/Engine>
#include <KTextTemplate/MetaType>
#include <KTextTemplate/Template>
#include <Prison/Barcode>

#include <QGuiApplication>
#include <QPalette>
using namespace Qt::Literals::StringLiterals;

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

    const auto dir = nodeHelper->createTempDir(u"semantic"_s);
    auto c = MessageViewer::MessagePartRendererManager::self()->createContext();

    QVariantMap style;
    style.insert(u"expandIcon"_s, QString(u"file://"_s + MessageViewer::IconNameCache::instance()->iconPathFromLocal(u"quoteexpand.png"_s)));
    style.insert(u"collapseIcon"_s, QString(u"file://"_s + MessageViewer::IconNameCache::instance()->iconPathFromLocal(u"quotecollapse.png"_s)));
    style.insert(u"palette"_s, QGuiApplication::palette());
    style.insert(u"viewScheme"_s, QVariant::fromValue(KColorScheme(QPalette::Normal, KColorScheme::View)));
    c.insert(u"style"_s, style);

    const bool testMode = qEnvironmentVariableIsSet("BPF_ITINERARY_TESTMODE"); // ensure deterministic results for unit tests
    QVariantMap actionState;
    actionState.insert(u"canShowCalendar"_s, memento->startDate().isValid());
    actionState.insert(u"canAddToCalendar"_s, memento->canAddToCalendar());
    actionState.insert(u"hasItineraryApp"_s, ItineraryUrlHandler::hasItineraryApp() || testMode);
    if (!testMode) {
        const auto devices = m_kdeConnect->devices();
        actionState.insert(u"canSendToDevice"_s, !devices.isEmpty());
        if (devices.size() == 1) {
            actionState.insert(u"defaultDeviceName"_s, devices[0].name);
            actionState.insert(u"defaultDeviceId"_s, devices[0].deviceId);
        }
    }
    c.insert(u"actionState"_s, actionState);

    // Grantlee can't do indexed map/array lookups, so we need to interleave this here already
    QVariantList elems;
    elems.reserve(extractedData.size());
    int ticketTokenId = 0;
    for (int i = 0; i < extractedData.size(); ++i) {
        QVariantMap data;
        QVariantMap state;
        const auto d = extractedData.at(i);
        state.insert(u"expanded"_s, d.expanded);
        data.insert(u"state"_s, state);
        data.insert(u"groupId"_s, i);

        QList<QVariant> reservations;
        reservations.reserve(d.reservations.count());
        for (const auto &r : d.reservations) {
            QVariantMap m;
            m.insert(u"reservation"_s, r);

            // generate ticket barcodes
            const auto ticket = JsonLd::convert<Reservation>(r).reservedTicket().value<Ticket>();
            std::optional<Prison::Barcode> barcode;
            switch (ticket.ticketTokenType()) {
            case Token::AztecCode:
                barcode = Prison::Barcode::create(Prison::Aztec);
                break;
            case Token::QRCode:
                barcode = Prison::Barcode::create(Prison::QRCode);
                break;
            case Token::DataMatrix:
                barcode = Prison::Barcode::create(Prison::DataMatrix);
                break;
            case Token::Code128:
                barcode = Prison::Barcode::create(Prison::Code128);
                break;
            case Token::PDF417:
                barcode = Prison::Barcode::create(Prison::PDF417);
                break;
            default:
                break;
            }
            if (barcode) {
                const QVariant barcodeContent = ticket.ticketTokenData();
                if (barcodeContent.userType() == QMetaType::QString) {
                    barcode->setData(barcodeContent.toString());
                } else {
                    barcode->setData(barcodeContent.toByteArray());
                }

                const auto img = barcode->toImage(barcode->preferredSize(qGuiApp->devicePixelRatio()));
                const QString fileName = dir + "/ticketToken"_L1 + QString::number(ticketTokenId++) + ".png"_L1;
                img.save(fileName);
                m.insert(u"ticketToken"_s, fileName);
                nodeHelper->addTempFile(fileName);
            }

            reservations.push_back(m);
        }
        data.insert(u"reservations"_s, QVariant::fromValue(reservations));
        elems.push_back(data);
    }
    c.insert(u"data"_s, elems);

    auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(u"org.kde.messageviewer/itinerary/itinerary.html"_s);
    const_cast<KTextTemplate::Engine *>(t->engine())->addDefaultLibrary(u"kitinerary_ktexttemplate_extension"_s);
    dynamic_cast<GrantleeTheme::Engine *>(const_cast<KTextTemplate::Engine *>(t->engine()))
        ->localizer()
        ->setApplicationDomain(QByteArrayLiteral("messageviewer_semantic_plugin"));
    KTextTemplate::OutputStream s(htmlWriter->stream());
    t->render(&s, &c);
    qobject_cast<GrantleeTheme::Engine *>(const_cast<KTextTemplate::Engine *>(t->engine()))
        ->localizer()
        ->setApplicationDomain(QByteArrayLiteral("libmessageviewer6"));
    return false; // yes, false, we want the rest of the email rendered normally after this
}

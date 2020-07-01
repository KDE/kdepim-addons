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

#include "itineraryprocessor.h"
#include "itinerarymemento.h"
#include "itinerary_debug.h"

#include <KItinerary/CreativeWork>
#include <KItinerary/DocumentUtil>
#include <KItinerary/ExtractorEngine>
#include <KItinerary/Event>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/Reservation>

#include <KPkPass/Pass>

#include <QJsonArray>
#include <QJsonDocument>

using namespace KItinerary;

static bool isPkPassContent(KMime::Content *content)
{
    const auto ct = content->contentType();
    const QByteArray mimetype = ct->mimeType();
    if (mimetype == "application/vnd.apple.pkpass") {
        return true;
    }
    if (mimetype != "application/octet-stream" && mimetype != "application/zip") {
        return false;
    }
    if (ct->name().endsWith(QLatin1String("pkpass"))) {
        return true;
    }
    const auto cd = content->contentDisposition(false);
    return cd && cd->filename().endsWith(QLatin1String("pkpass"));
}

static bool isCalendarContent(KMime::Content *content)
{
    const auto ct = content->contentType();
    const QByteArray mimetype = ct ? ct->mimeType() : QByteArray();
    if (mimetype == "text/calendar") {
        return true;
    }
    if (mimetype != "text/plain" && mimetype != "application/octet-stream") {
        return false;
    }
    if (ct && ct->name().endsWith(QLatin1String(".ics"))) {
        return true;
    }
    const auto cd = content->contentDisposition(false);
    return cd && cd->filename().endsWith(QLatin1String(".ics"));
}

ItineraryProcessor::ItineraryProcessor() = default;
ItineraryProcessor::~ItineraryProcessor() = default;

MimeTreeParser::MessagePart::Ptr ItineraryProcessor::process(MimeTreeParser::Interface::BodyPart &part) const
{
    auto nodeHelper = part.nodeHelper();
    if (!nodeHelper) {
        return {};
    }

    // determine sender date of the current part (differs from topLevel()->date() for forwarded mails
    QDateTime senderDateTime;
    auto node = part.content();
    auto dateHdr = node->header<KMime::Headers::Date>();
    while (!dateHdr && node->parent()) {
        node = node->parent();
        dateHdr = node->header<KMime::Headers::Date>();
    }
    if (dateHdr) {
        senderDateTime = dateHdr->dateTime();
    }

    auto memento = dynamic_cast<ItineraryMemento *>(nodeHelper->bodyPartMemento(part.topLevelContent(), ItineraryMemento::identifier()));
    if (!memento) {
        memento = new ItineraryMemento;
        memento->setMessageDate(senderDateTime);
        nodeHelper->setBodyPartMemento(part.topLevelContent(), ItineraryMemento::identifier(), memento);
    }

    // check if we still have to do anything at all
    if (memento->isParsed(part.content()->index())) {
        return {};
    }
    memento->setParsed(part.content()->index());

    std::unique_ptr<KPkPass::Pass> pass;
    bool isPdf = false;

    ExtractorEngine engine;
    engine.setUseSeparateProcess(true);
    engine.setContext(part.content());
    if (isPkPassContent(part.content())) {
        pass.reset(KPkPass::Pass::fromData(part.content()->decodedContent()));
        engine.setPass(pass.get());
    } else if (part.content()->contentType()->isHTMLText()) {
        engine.setData(part.content()->decodedContent(), ExtractorInput::Html);
    } else if (part.content()->contentType()->mimeType() == "application/pdf" || part.content()->contentType()->name().endsWith(QLatin1String(".pdf"), Qt::CaseInsensitive)) {
        isPdf = true;
        engine.setData(part.content()->decodedContent(), ExtractorInput::Pdf);
    } else if (isCalendarContent(part.content())) {
        engine.setData(part.content()->decodedContent(), ExtractorInput::ICal);
    } else if (part.content()->contentType()->isPlainText()) {
        engine.setText(part.content()->decodedText());
    } else {
        // we have extractors but this isn't a mimetype we understand
        return {};
    }

    const auto data = engine.extract();
    //qCDebug(ITINERARY_LOG).noquote() << QJsonDocument(data).toJson();
    auto decodedData = JsonLdDocument::fromJson(data);

    for (auto it = decodedData.begin(); it != decodedData.end(); ++it) {
        if (JsonLd::isA<Event>(*it)) { // promote Event to EventReservation
            EventReservation res;
            res.setReservationFor(*it);
            *it = res;
        }
    }

    if (!decodedData.isEmpty()) {
        if (isPdf) {
            const auto docData = part.content()->decodedContent();
            const auto docId = DocumentUtil::idForContent(docData);
            DigitalDocument docInfo;
            docInfo.setEncodingFormat(QStringLiteral("application/pdf"));
            docInfo.setName(MimeTreeParser::NodeHelper::fileName(part.content()));
            memento->addDocument(docId, docInfo, docData);

            for (auto &res : decodedData) {
                DocumentUtil::addDocumentId(res, docId);
            }
        }

        memento->appendData(decodedData);
    }

    if (pass) {
        memento->addPass(pass.get(), part.content()->decodedContent());
    }

    qCDebug(ITINERARY_LOG) << "-------------------------------------------- END ITINERARY PARSING";
    return {};
}

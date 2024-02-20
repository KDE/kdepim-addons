/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itineraryprocessor.h"
#include "itinerary_debug.h"
#include "itinerarymemento.h"

#include <KItinerary/CreativeWork>
#include <KItinerary/DocumentUtil>
#include <KItinerary/Event>
#include <KItinerary/ExtractorDocumentNode>
#include <KItinerary/ExtractorDocumentNodeFactory>
#include <KItinerary/ExtractorEngine>
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
    if (mimetype == QByteArrayLiteral("application/vnd.apple.pkpass")) {
        return true;
    }
    if (mimetype != QByteArrayLiteral("application/octet-stream") && mimetype != QByteArrayLiteral("application/zip")) {
        return false;
    }
    if (ct->name().endsWith(QLatin1StringView("pkpass"))) {
        return true;
    }
    const auto cd = content->contentDisposition(false);
    return cd && cd->filename().endsWith(QLatin1StringView("pkpass"));
}

static bool isCalendarContent(KMime::Content *content)
{
    const auto ct = content->contentType();
    const QByteArray mimetype = ct ? ct->mimeType() : QByteArray();
    if (mimetype == QByteArrayLiteral("text/calendar") || mimetype == QByteArrayLiteral("application/ics")) {
        return true;
    }
    if (mimetype != QByteArrayLiteral("text/plain") && mimetype != QByteArrayLiteral("application/octet-stream")) {
        return false;
    }
    if (ct && ct->name().endsWith(QLatin1StringView(".ics"))) {
        return true;
    }
    const auto cd = content->contentDisposition(false);
    return cd && cd->filename().endsWith(QLatin1StringView(".ics"));
}

static KMime::Content *findMultipartRelatedParent(KMime::Content *node)
{
    while (node) {
        if (node->contentType()->mimeType() == QByteArrayLiteral("multipart/related")) {
            return node;
        }
        node = node->parent();
    }
    return nullptr;
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
    bool contextIsToplevel = false;
    QDateTime senderDateTime;
    auto node = part.content();
    auto dateHdr = node->header<KMime::Headers::Date>();
    while (!dateHdr && node->parent()) {
        node = node->parent();
        dateHdr = node->header<KMime::Headers::Date>();
    }
    if (!dateHdr) { // search outside of the current MIME tree if necessary, relevant e.g. for encrypted nodes
        node = part.topLevelContent();
        if (node) {
            contextIsToplevel = true;
        }
        while (!dateHdr && node) {
            dateHdr = node->header<KMime::Headers::Date>();
            node = node->parent();
        }
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
    engine.setContext(QVariant::fromValue<KMime::Content *>(contextIsToplevel ? part.topLevelContent() : part.content()), u"message/rfc822");
    if (isPkPassContent(part.content())) {
        pass.reset(KPkPass::Pass::fromData(part.content()->decodedContent()));
        engine.setContent(QVariant::fromValue<KPkPass::Pass *>(pass.get()), u"application/vnd.apple.pkpass");
    } else if (part.content()->contentType()->isHTMLText()) {
        engine.setContent(part.content()->decodedText(), u"text/html");
        // find embedded images that belong to this HTML part, and create child-nodes for those
        // this is needed for finding barcodes in those images
        if (const auto rootNode = findMultipartRelatedParent(part.content())) {
            const auto children = rootNode->contents();
            for (const auto node : children) {
                const auto ct = node->contentType(false);
                if (!ct || !node->contentID(false)) {
                    continue;
                }
                if (ct->mimeType() == QByteArrayLiteral("image/png") || ct->mimeType() == QByteArrayLiteral("image/gif")) {
                    auto pngNode = engine.documentNodeFactory()->createNode(node->decodedContent(), {}, QString::fromUtf8(ct->mimeType()));
                    engine.rootDocumentNode().appendChild(pngNode);
                }
            }
        }
    } else if (part.content()->contentType()->mimeType() == "application/pdf"
               || part.content()->contentType()->name().endsWith(QLatin1StringView(".pdf"), Qt::CaseInsensitive)) {
        isPdf = true;
        engine.setData(part.content()->decodedContent());
    } else if (isCalendarContent(part.content())) {
        engine.setData(part.content()->decodedContent());
    } else if (part.content()->contentType()->isPlainText()) {
        engine.setContent(part.content()->decodedText(), u"text/plain");
    } else {
        return {};
    }

    const auto data = engine.extract();
    // qCDebug(ITINERARY_LOG).noquote() << QJsonDocument(data).toJson();
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

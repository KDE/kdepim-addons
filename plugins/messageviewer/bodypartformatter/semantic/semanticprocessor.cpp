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

#include "semanticprocessor.h"
#include "semanticmemento.h"
#include "semantic_debug.h"

#include <KItinerary/ExtractorEngine>
#include <KItinerary/HtmlDocument>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/PdfDocument>

#include <KPkPass/Pass>

#include <KCalCore/MemoryCalendar>
#include <KCalCore/ICalFormat>

#include <QJsonArray>
#include <QJsonDocument>

using namespace KItinerary;

static bool isPkPassContent(KMime::Content *content)
{
    const auto ct = content->contentType();
    if (ct->mimeType() == "application/vnd.apple.pkpass") {
        return true;
    }
    if (ct->mimeType() != "application/octet-stream" && ct->mimeType() != "application/zip") {
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
    if (ct->mimeType() == "text/calendar") {
        return true;
    }
    if (ct->mimeType() != "text/plain" && ct->mimeType() != "application/octet-stream") {
        return false;
    }
    if (ct->name().endsWith(QLatin1String(".ics"))) {
        return true;
    }
    const auto cd = content->contentDisposition(false);
    return cd && cd->filename().endsWith(QLatin1String(".ics"));
}

SemanticProcessor::SemanticProcessor() = default;
SemanticProcessor::~SemanticProcessor() = default;

MimeTreeParser::MessagePart::Ptr SemanticProcessor::process(MimeTreeParser::Interface::BodyPart &part) const
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

    auto memento = dynamic_cast<SemanticMemento *>(nodeHelper->bodyPartMemento(part.topLevelContent(), "org.kde.messageviewer.semanticData"));
    if (!memento) {
        memento = new SemanticMemento;
        memento->setMessageDate(senderDateTime);
        nodeHelper->setBodyPartMemento(part.topLevelContent(), "org.kde.messageviewer.semanticData", memento);
    }

    // check if we still have to do anything at all
    if (memento->isParsed(part.content()->index())) {
        return {};
    }
    memento->setParsed(part.content()->index());

    std::vector<const Extractor *> extractors;
    std::unique_ptr<KPkPass::Pass> pass;
    std::unique_ptr<PdfDocument> pdfDoc;
    std::unique_ptr<HtmlDocument> htmlDoc;
    KCalCore::Calendar::Ptr calendar;

    ExtractorEngine engine;
    engine.setContext(part.content());
    if (isPkPassContent(part.content())) {
        pass.reset(KPkPass::Pass::fromData(part.content()->decodedContent()));
        engine.setPass(pass.get());
    } else if (part.content()->contentType()->isHTMLText()) {
        htmlDoc.reset(HtmlDocument::fromData(part.content()->decodedContent()));
        engine.setHtmlDocument(htmlDoc.get());
    } else if (part.content()->contentType()->mimeType() == "application/pdf") {
        pdfDoc.reset(PdfDocument::fromData(part.content()->decodedContent()));
        engine.setPdfDocument(pdfDoc.get());
    } else if (isCalendarContent(part.content())) {
        calendar.reset(new KCalCore::MemoryCalendar(QTimeZone()));
        KCalCore::ICalFormat format;
        if (format.fromRawString(calendar, part.content()->decodedContent())) {
            engine.setCalendar(calendar);
        }
    } else if (part.content()->contentType()->isPlainText()) {
        engine.setText(part.content()->decodedText());
    } else {
        // we have extractors but this isn't a mimetype we understand
        return {};
    }

    const auto data = engine.extract();
    qCDebug(SEMANTIC_LOG).noquote() << QJsonDocument(data).toJson();
    const auto decodedData = JsonLdDocument::fromJson(data);
    if (!decodedData.isEmpty()) {
        memento->appendData(decodedData);
    }

    if (pass) {
        memento->addPass(pass.get(), part.content()->decodedContent());
    }

    qCDebug(SEMANTIC_LOG) << "-------------------------------------------- END SEMANTIC PARSING";
    return {};
}

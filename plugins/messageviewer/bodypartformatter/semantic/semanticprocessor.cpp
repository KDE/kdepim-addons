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
#include <KItinerary/ExtractorPreprocessor>
#include <KItinerary/ExtractorPostprocessor>
#include <KItinerary/HtmlDocument>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/PdfDocument>
#include <KItinerary/StructuredDataExtractor>

#include <KPkPass/Pass>

#include <QJsonArray>
#include <QJsonDocument>

using namespace KItinerary;

std::weak_ptr<ExtractorRepository> SemanticProcessor::s_repository;

SemanticProcessor::SemanticProcessor()
{
    m_repository = s_repository.lock();
    if (!m_repository) {
        m_repository.reset(new ExtractorRepository);
        s_repository = m_repository;
    }
}

SemanticProcessor::~SemanticProcessor() = default;

MimeTreeParser::MessagePart::Ptr SemanticProcessor::process(MimeTreeParser::Interface::BodyPart &part) const
{
    auto nodeHelper = part.nodeHelper();
    if (!nodeHelper) {
        return {};
    }
    auto memento = dynamic_cast<SemanticMemento *>(nodeHelper->bodyPartMemento(part.topLevelContent(), "org.kde.messageviewer.semanticData"));
    if (!memento) {
        memento = new SemanticMemento;
        memento->setMessageDate(static_cast<KMime::Message *>(part.content()->topLevel())->date()->dateTime());
        nodeHelper->setBodyPartMemento(part.topLevelContent(), "org.kde.messageviewer.semanticData", memento);
    }

    // check if we still have to do anything at all
    if (memento->isParsed(part.content()->index())) {
        return {};
    }
    memento->setParsed(part.content()->index());

    qCDebug(SEMANTIC_LOG) << "-------------------------------------------- BEGIN SEMANTIC PARSING";
    qCDebug(SEMANTIC_LOG) << part.content()->contentType()->mimeType();

    // look for structured data first, cheaper and better quality
    if (part.content()->contentType()->isHTMLText()) {
        StructuredDataExtractor extractor;
        extractor.parse(part.content()->decodedText());

        const auto data = extractor.data();
        const auto decodedData = JsonLdDocument::fromJson(data);
        if (data.size() != decodedData.size()) {
            qCDebug(SEMANTIC_LOG).noquote() << "Unhandled content:" << QJsonDocument(data).toJson();
        }
        if (!decodedData.isEmpty()) {
            memento->appendStructuredData(decodedData);
            qCDebug(SEMANTIC_LOG) << "Found structured data:" << decodedData;
            return {};
        }
    }

    // try the unstructured data extractor as a fallback
    std::vector<const Extractor *> extractors;
    std::unique_ptr<KPkPass::Pass> pass;
    if (part.content()->contentType()->mimeType() == "application/vnd.apple.pkpass") {
        pass.reset(KPkPass::Pass::fromData(part.content()->decodedContent()));
        extractors = m_repository->extractorsForPass(pass.get());
    } else {
        extractors = m_repository->extractorsForMessage(part.content());
    }
    if (extractors.empty()) {
        qCDebug(SEMANTIC_LOG) << "Found no suitable extractors.";
        return {};
    }
    qCDebug(SEMANTIC_LOG) << "Found unstructured extractor rules for message" << extractors.size();

    ExtractorPreprocessor preproc;
    std::unique_ptr<PdfDocument> pdfDoc;
    std::unique_ptr<HtmlDocument> htmlDoc;
    if (part.content()->contentType()->isPlainText()) {
        preproc.preprocessPlainText(part.content()->decodedText());
    } else if (part.content()->contentType()->isHTMLText()) {
        htmlDoc.reset(HtmlDocument::fromData(part.content()->decodedText().toUtf8()));
        preproc.preprocessHtml(part.content()->decodedText());
    } else if (part.content()->contentType()->mimeType() == "application/pdf") {
        pdfDoc.reset(PdfDocument::fromData(part.content()->decodedContent()));
    }

    ExtractorEngine engine;
    engine.setSenderDate(static_cast<KMime::Message *>(part.content()->topLevel())->date()->dateTime());
    engine.setText(preproc.text());
    engine.setPass(pass.get());
    engine.setHtmlDocument(htmlDoc.get());
    engine.setPdfDocument(pdfDoc.get());
    for (auto extractor : extractors) {
        engine.setExtractor(extractor);
        const auto data = engine.extract();
        qCDebug(SEMANTIC_LOG).noquote() << QJsonDocument(data).toJson();
        const auto decodedData = JsonLdDocument::fromJson(data);
        if (!decodedData.isEmpty()) {
            memento->appendStructuredData(decodedData);
            break;
        }
    }

    if (pass) {
        memento->addPass(pass.get(), part.content()->decodedContent());
    }

    qCDebug(SEMANTIC_LOG) << "-------------------------------------------- END SEMANTIC PARSING";
    return {};
}

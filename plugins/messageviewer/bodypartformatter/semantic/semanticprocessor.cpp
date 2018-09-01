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
#include <KItinerary/HtmlDocument>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/PdfDocument>

#include <KPkPass/Pass>

#include <QJsonArray>
#include <QJsonDocument>

using namespace KItinerary;

std::weak_ptr<ExtractorRepository> SemanticProcessor::s_repository;

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

    std::vector<const Extractor *> extractors;
    std::unique_ptr<KPkPass::Pass> pass;
    if (isPkPassContent(part.content())) {
        pass.reset(KPkPass::Pass::fromData(part.content()->decodedContent()));
        extractors = m_repository->extractorsForPass(pass.get());
    } else {
        extractors = m_repository->extractorsForMessage(part.content());
    }
    if (extractors.empty()) {
        qCDebug(SEMANTIC_LOG) << "Found no suitable extractors.";
        return {};
    }

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
    } else if (!pass) {
        // we have extractors but this isn't a mimetype we understand
        return {};
    }

    ExtractorEngine engine;
    engine.setSenderDate(static_cast<KMime::Message *>(part.content()->topLevel())->date()->dateTime());
    engine.setText(preproc.text());
    engine.setPass(pass.get());
    engine.setHtmlDocument(htmlDoc.get());
    engine.setPdfDocument(pdfDoc.get());
    engine.setExtractors(std::move(extractors));
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

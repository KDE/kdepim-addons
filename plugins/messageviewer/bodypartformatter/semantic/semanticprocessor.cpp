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
#include "extractorengine.h"
#include "extractorpreprocessor.h"
#include "jsonlddocument.h"
#include "structureddataextractor.h"
#include "semanticmemento.h"
#include "semantic_debug.h"

#include <QDebug>
#include <QJsonDocument>

MimeTreeParser::MessagePart::Ptr SemanticProcessor::process(MimeTreeParser::Interface::BodyPart &part) const
{
    auto nodeHelper = part.nodeHelper();
    if (!nodeHelper) {
        return {};
    }
    auto memento = dynamic_cast<SemanticMemento *>(nodeHelper->bodyPartMemento(part.topLevelContent(), "org.kde.messageviewer.semanticData"));
    if (!memento) {
        memento = new SemanticMemento;
        nodeHelper->setBodyPartMemento(part.topLevelContent(), "org.kde.messageviewer.semanticData", memento);
    }

    // check if we still have to do anything at all
    if (memento->hasStructuredData()) {
        return {};
    }
    if (memento->isParsed(part.content()->index())) {
        return {};
    }
    memento->setParsed(part.content()->index());

    qCDebug(SEMANTIC_LOG) << "-------------------------------------------- BEGIN SEMANTIC PARSING";
    qCDebug(SEMANTIC_LOG) << part.content()->contentType()->mimeType();

    // look for structured data first, cheaper and better quality
    if (part.content()->contentType()->mimeType() == "text/html") {
        StructuredDataExtractor extractor;
        extractor.parse(part.content()->decodedText());

        const auto data = extractor.data();
        const auto decodedData = JsonLdDocument::fromJson(data);
        if (data.size() != decodedData.size()) {
            qCDebug(SEMANTIC_LOG) << "Unhandled content:" << QJsonDocument(data).toJson();
        }
        if (!decodedData.isEmpty()) {
            memento->setData(decodedData);
            memento->setStructuredDataFound(true);
            qCDebug(SEMANTIC_LOG) << "Found structured data:" << decodedData;
        }
    }

    // try the unstructured data extractor as a fallback
    if (memento->isEmpty()) {
        const auto extractors = m_repository.extractorsForMessage(part.content());
        if (extractors.empty()) {
            return {};
        }
        qCDebug(SEMANTIC_LOG) << "Found unstructured extractor rules for message" << extractors.size();

        ExtractorPreprocessor preproc;
        if (part.content()->contentType()->isPlainText()) {
            preproc.preprocessPlainText(part.content()->decodedText());
        } else if (part.content()->contentType()->isHTMLText()) {
            preproc.preprocessHtml(part.content()->decodedText());
        } else if (part.content()->contentType()->mimeType() == "application/pdf") {
            preproc.preprocessPdf(part.content()->decodedContent());
        } else {
            return {};
        }

        ExtractorEngine engine;
        engine.setExtractor(extractors.at(0));
        engine.setText(preproc.text());
        const auto data = engine.extract();
        qCDebug(SEMANTIC_LOG).noquote() << QJsonDocument(data).toJson();
        const auto decodedData = JsonLdDocument::fromJson(data);
        if (!decodedData.isEmpty()) {
            memento->setData(decodedData);
        }
    }

    // TODO postprocessor to filter incomplete/broken elements and merge duplicates

    qCDebug(SEMANTIC_LOG) << "-------------------------------------------- END SEMANTIC PARSING";
    return {};
}

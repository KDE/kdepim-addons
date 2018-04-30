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

#ifndef SEMANTICMEMENTO_H
#define SEMANTICMEMENTO_H

#include <MimeTreeParser/BodyPart>

#include <KItinerary/ExtractorPostprocessor>

#include <QSet>
#include <QVariant>
#include <QVector>

#include <vector>

namespace KPkPass {
class Pass;
}

namespace KMime {
class ContentIndex;
}

class QDateTime;

/** Memento holding the semantic information extracted for an email. */
class SemanticMemento : public MimeTreeParser::Interface::BodyPartMemento
{
public:
    ~SemanticMemento() override = default;
    void detach() override;

    bool isParsed(const KMime::ContentIndex &index) const;
    void setParsed(const KMime::ContentIndex &index);

    void setMessageDate(const QDateTime &contextDt);
    void appendUnstructuredData(const QVector<QVariant> &data);
    void appendStructuredData(const QVector<QVariant> &data);

    QVector<QVariant> extractedData();

    QVector<bool> expanded() const;
    void toggleExpanded(int index);

    void addPass(KPkPass::Pass *pass, const QByteArray &rawData);
    QByteArray rawPassData(const QString &passTypeIdentifier, const QString &serialNumber) const;

private:
    QVector<QVariant> m_pendingStructuredData;
    QVector<bool> m_expanded;
    QSet<KMime::ContentIndex> m_parsedParts;
    KItinerary::ExtractorPostprocessor m_postProc;

    struct PassData {
        QString passTypeIdentifier;
        QString serialNumber;
        QByteArray rawData;
    };
    std::vector<PassData> m_passes;
};

#endif // SEMANTICMEMENTO_H

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

#ifndef ITINERARYMEMENTO_H
#define ITINERARYMEMENTO_H

#include <MimeTreeParser/BodyPart>

#include <KItinerary/ExtractorPostprocessor>
#include <KCalendarCore/Event>

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

/** Memento holding the itinerary information extracted for an email. */
class ItineraryMemento : public MimeTreeParser::Interface::BodyPartMemento
{
public:
    ~ItineraryMemento() override = default;
    void detach() override;

    static const char* identifier();

    bool isParsed(const KMime::ContentIndex &index) const;
    void setParsed(const KMime::ContentIndex &index);

    void setMessageDate(const QDateTime &contextDt);
    void appendData(const QVector<QVariant> &data);

    bool hasData() const;
    struct TripData {
        QVector<QVariant> reservations;
        KCalendarCore::Event::Ptr event;
        bool expanded;
    };
    QVector<TripData> data();
    void toggleExpanded(int index);

    void addPass(KPkPass::Pass *pass, const QByteArray &rawData);
    QByteArray rawPassData(const QString &passTypeIdentifier, const QString &serialNumber) const;

    struct PassData {
        QString passTypeIdentifier;
        QString serialNumber;
        QByteArray rawData;
    };
    const std::vector<PassData>& passData() const { return m_passes; }

    struct DocumentData {
        QString docId;
        QVariant docInfo;
        QByteArray rawData;
    };
    const std::vector<DocumentData>& documentData() const { return m_docs; }
    void addDocument(const QString &docId, const QVariant &docInfo, const QByteArray &docData);

private:
    QSet<KMime::ContentIndex> m_parsedParts;
    KItinerary::ExtractorPostprocessor m_postProc;
    QVector<TripData> m_data;
    std::vector<PassData> m_passes;
    std::vector<DocumentData> m_docs;
};

#endif // ITINERARYMEMENTO_H

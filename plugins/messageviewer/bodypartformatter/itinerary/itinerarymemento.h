/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ITINERARYMEMENTO_H
#define ITINERARYMEMENTO_H

#include <MimeTreeParser/BodyPart>

#include <KCalendarCore/Event>
#include <KItinerary/ExtractorPostprocessor>

#include <QSet>
#include <QVariant>
#include <QVector>

#include <vector>

namespace KPkPass
{
class Pass;
}

namespace KMime
{
class ContentIndex;
}

class QDateTime;

/** Memento holding the itinerary information extracted for an email. */
class ItineraryMemento : public MimeTreeParser::Interface::BodyPartMemento
{
public:
    ItineraryMemento();
    ~ItineraryMemento() override = default;
    void detach() override;

    static const char *identifier();

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
    const std::vector<PassData> &passData() const
    {
        return m_passes;
    }

    struct DocumentData {
        QString docId;
        QVariant docInfo;
        QByteArray rawData;
    };
    const std::vector<DocumentData> &documentData() const
    {
        return m_docs;
    }

    void addDocument(const QString &docId, const QVariant &docInfo, const QByteArray &docData);

    /** At least one reservation has enough information to add it to the calendar. */
    bool canAddToCalendar() const;
    /** Start date of the reservation data.
     *  TODO this eventually should include the end date too, for showing the full range in the calendar,
     *  but KOrganizer doesn't support that yet
     */
    QDate startDate() const;

private:
    QSet<KMime::ContentIndex> m_parsedParts;
    KItinerary::ExtractorPostprocessor m_postProc;
    QVector<TripData> m_data;
    std::vector<PassData> m_passes;
    std::vector<DocumentData> m_docs;
};

#endif // ITINERARYMEMENTO_H

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

#include "itinerarymemento.h"

#include <CalendarSupport/CalendarSingleton>

#include <KItinerary/CalendarHandler>
#include <KItinerary/JsonLdDocument>
#include <KItinerary/MergeUtil>
#include <KItinerary/Reservation>

#include <KPkPass/Pass>

#include <KMime/ContentIndex>

using namespace KItinerary;

void ItineraryMemento::detach()
{
}

const char *ItineraryMemento::identifier()
{
    return "org.kde.messageviewer.itineraryData";
}

bool ItineraryMemento::isParsed(const KMime::ContentIndex &index) const
{
    return m_parsedParts.contains(index);
}

void ItineraryMemento::setParsed(const KMime::ContentIndex &index)
{
    m_parsedParts.insert(index);
}

void ItineraryMemento::setMessageDate(const QDateTime &contextDt)
{
    m_postProc.setContextDate(contextDt);
}

void ItineraryMemento::appendData(const QVector<QVariant> &data)
{
    m_postProc.process(data);
}

bool ItineraryMemento::hasData() const
{
    return !m_data.isEmpty() || !m_postProc.result().isEmpty();
}

QVector<ItineraryMemento::TripData> ItineraryMemento::data()
{
    if (m_data.isEmpty() && !m_postProc.result().isEmpty()) {
        // perform calendar lookup and merge results
        std::vector<std::pair<QVariant, KCalendarCore::Event::Ptr> > resolvedEvents;
        resolvedEvents.reserve(m_postProc.result().size());
        const auto calendar = CalendarSupport::calendarSingleton(qEnvironmentVariableIsSet("BPF_ITINERARY_NO_AKONADI") ? false : true);
        for (const auto &r : m_postProc.result()) {
            auto e = std::make_pair(r, CalendarHandler::findEvent(calendar, r));
            if (e.second) {
                const auto existingRes = CalendarHandler::reservationsForEvent(e.second);
                for (const auto &ev : existingRes) {
                    if (MergeUtil::isSame(ev, e.first)) {
                        e.first = MergeUtil::merge(ev, e.first);
                        break;
                    }
                }
            }
            resolvedEvents.push_back(e);
        }

        // merge multi-traveler elements
        for (auto it = resolvedEvents.begin(); it != resolvedEvents.end();) {
            TripData data;
            data.reservations.push_back((*it).first);
            data.event = (*it).second;
            data.expanded = false;
            ++it;

            if (JsonLd::canConvert<Reservation>(data.reservations.at(0))) {
                const auto trip = JsonLd::convert<Reservation>(data.reservations.at(0)).reservationFor();
                for (; it != resolvedEvents.end(); ++it) {
                    if (!JsonLd::canConvert<Reservation>((*it).first) || !MergeUtil::isSame(JsonLd::convert<Reservation>((*it).first).reservationFor(), trip)) {
                        break;
                    }
                    data.reservations.push_back((*it).first);
                }

                // add other traveler we already know about from previous data in the calendar
                // but that aren't in the currently extracted data set
                if (data.event) {
                    for (const auto &prev : CalendarHandler::reservationsForEvent(data.event)) {
                        const auto notFound = std::find_if(data.reservations.constBegin(), data.reservations.constEnd(), [prev](const QVariant &v) {
                            return MergeUtil::isSame(v, prev);
                        }) == data.reservations.constEnd();
                        if (notFound) {
                            data.reservations.push_back(prev);
                        }
                    }
                }
            }

            m_data.push_back(data);
        }
    }

    return m_data;
}

void ItineraryMemento::toggleExpanded(int index)
{
    if (index >= m_data.size()) {
        return;
    }
    m_data[index].expanded = !m_data.at(index).expanded;
}

void ItineraryMemento::addPass(KPkPass::Pass *pass, const QByteArray &rawData)
{
    m_passes.emplace_back(PassData{pass->passTypeIdentifier(), pass->serialNumber(), rawData});
}

QByteArray ItineraryMemento::rawPassData(const QString &passTypeIdentifier, const QString &serialNumber) const
{
    for (const auto &pass : m_passes) {
        if (pass.passTypeIdentifier == passTypeIdentifier && pass.serialNumber == serialNumber) {
            return pass.rawData;
        }
    }
    return {};
}

void ItineraryMemento::addDocument(const QString &docId, const QVariant &docInfo, const QByteArray &docData)
{
    m_docs.push_back({docId, docInfo, docData});
}

/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itinerarymemento.h"

#include <CalendarSupport/CalendarSingleton>

#include <KItinerary/CalendarHandler>
#include <KItinerary/ExtractorValidator>
#include <KItinerary/Flight>
#include <KItinerary/MergeUtil>
#include <KItinerary/Reservation>
#include <KItinerary/SortUtil>

#include <KPkPass/Pass>

#include <KMime/ContentIndex>

using namespace KItinerary;

ItineraryMemento::ItineraryMemento()
{
    m_postProc.setValidationEnabled(false);
}

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
        // filter out types we can't handle, but keep incomplete elements to see if we can complete them from the calendar
        ExtractorValidator validator;
        validator.setAcceptedTypes<BoatReservation,
                                   BusReservation,
                                   EventReservation,
                                   FlightReservation,
                                   FoodEstablishmentReservation,
                                   LodgingReservation,
                                   RentalCarReservation,
                                   TaxiReservation,
                                   TrainReservation>();
        validator.setAcceptOnlyCompleteElements(false);
        auto postProcResult = m_postProc.result();
        postProcResult.erase(std::remove_if(postProcResult.begin(),
                                            postProcResult.end(),
                                            [&validator](const auto &elem) {
                                                return !validator.isValidElement(elem);
                                            }),
                             postProcResult.end());

        // perform calendar lookup and merge results
        std::vector<std::pair<QVariant, KCalendarCore::Event::Ptr>> resolvedEvents;
        resolvedEvents.reserve(postProcResult.size());
        const auto calendar = CalendarSupport::calendarSingleton(!qEnvironmentVariableIsSet("BPF_ITINERARY_TESTMODE"));
        for (const auto &r : std::as_const(postProcResult)) {
            const auto events = CalendarHandler::findEvents(calendar, r);
            if (events.empty()) {
                resolvedEvents.emplace_back(r, KCalendarCore::Event::Ptr());
                continue;
            }

            for (const auto &event : events) {
                const auto existingRes = CalendarHandler::reservationsForEvent(event);
                for (const auto &ev : existingRes) {
                    if (MergeUtil::isSame(ev, r)) {
                        resolvedEvents.emplace_back(MergeUtil::merge(ev, r), event);
                    }
                }
            }
        }

        // discard elemnents we couldn't complete from the calendar
        validator.setAcceptOnlyCompleteElements(true);
        resolvedEvents.erase(std::remove_if(resolvedEvents.begin(),
                                            resolvedEvents.end(),
                                            [&validator](const auto &p) {
                                                return !validator.isValidElement(p.first);
                                            }),
                             resolvedEvents.end());

        // merge multi-traveler elements
        for (auto it = resolvedEvents.begin(); it != resolvedEvents.end();) {
            TripData data;
            data.reservations.push_back((*it).first);
            data.event = (*it).second;
            data.expanded = false;
            ++it;

            if (JsonLd::canConvert<Reservation>(data.reservations.at(0))) {
                for (; it != resolvedEvents.end(); ++it) {
                    if (!MergeUtil::isSameIncidence(data.reservations.at(0), (*it).first)) {
                        break;
                    }
                    data.reservations.push_back((*it).first);
                }

                // add other traveler we already know about from previous data in the calendar
                // but that aren't in the currently extracted data set
                if (data.event) {
                    const auto reservationsForEvent = CalendarHandler::reservationsForEvent(data.event);
                    for (const auto &prev : reservationsForEvent) {
                        const auto notFound = std::find_if(data.reservations.constBegin(),
                                                           data.reservations.constEnd(),
                                                           [prev](const QVariant &v) {
                                                               return MergeUtil::isSame(v, prev);
                                                           })
                            == data.reservations.constEnd();
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

bool ItineraryMemento::canAddToCalendar() const
{
    for (const auto &d : m_data) {
        if (JsonLd::isA<FlightReservation>(d.reservations.at(0))) {
            const auto f = d.reservations.at(0).value<FlightReservation>().reservationFor().value<Flight>();
            if (f.departureTime().isValid() && f.arrivalTime().isValid()) {
                return true;
            }
            continue;
        } else if (SortUtil::startDateTime(d.reservations.at(0)).isValid()) {
            return true;
        }
    }
    return false;
}

QDate ItineraryMemento::startDate() const
{
    for (const auto &d : m_data) {
        const auto dt = SortUtil::startDateTime(d.reservations.at(0));
        if (dt.isValid()) {
            return dt.date();
        }
    }
    return {};
}

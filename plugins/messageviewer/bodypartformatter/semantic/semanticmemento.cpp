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

#include "semanticmemento.h"

#include <CalendarSupport/CalendarSingleton>

#include <KItinerary/CalendarHandler>
#include <KItinerary/JsonLdDocument>

#include <KPkPass/Pass>

#include <KMime/ContentIndex>

using namespace KItinerary;

void SemanticMemento::detach()
{
}

bool SemanticMemento::isParsed(const KMime::ContentIndex &index) const
{
    return m_parsedParts.contains(index);
}

void SemanticMemento::setParsed(const KMime::ContentIndex &index)
{
    m_parsedParts.insert(index);
}

void SemanticMemento::setMessageDate(const QDateTime &contextDt)
{
    m_postProc.setContextDate(contextDt);
}

void SemanticMemento::appendStructuredData(const QVector<QVariant> &data)
{
    m_pendingStructuredData.append(data);
}

void SemanticMemento::appendUnstructuredData(const QVector<QVariant> &data)
{
    m_postProc.process(data);
}

bool SemanticMemento::hasData() const
{
    return !m_data.isEmpty() || !m_pendingStructuredData.isEmpty() || !m_postProc.result().isEmpty();
}

QVector<SemanticMemento::ReservationData> SemanticMemento::data()
{
    if (!m_pendingStructuredData.isEmpty()) {
        m_postProc.process(m_pendingStructuredData);
        m_pendingStructuredData.clear();
    }

    if (m_data.isEmpty() && !m_postProc.result().isEmpty()) {
        const auto calendar = CalendarSupport::calendarSingleton(true);
        for (const auto &r : m_postProc.result()) {
            ReservationData data;
            data.res = r;
            data.expanded = false;

            data.event = CalendarHandler::findEvent(calendar, data.res);
            if (data.event) {
                const auto existingRes = CalendarHandler::reservationForEvent(data.event);
                data.res = JsonLdDocument::apply(existingRes, data.res);
            }

            m_data.push_back(data);
        }
    }

    return m_data;
}

void SemanticMemento::toggleExpanded(int index)
{
    if (index >= m_data.size()) {
        return;
    }
    m_data[index].expanded = !m_data.at(index).expanded;
}

void SemanticMemento::addPass(KPkPass::Pass *pass, const QByteArray &rawData)
{
    m_passes.emplace_back(PassData{pass->passTypeIdentifier(), pass->serialNumber(), rawData});
}

QByteArray SemanticMemento::rawPassData(const QString &passTypeIdentifier, const QString &serialNumber) const
{
    for (const auto &pass : m_passes) {
        if (pass.passTypeIdentifier == passTypeIdentifier && pass.serialNumber == serialNumber) {
            return pass.rawData;
        }
    }
    return {};
}

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

#include <KMime/ContentIndex>

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

void SemanticMemento::setMessageDate(const QDateTime& contextDt)
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

QVector<QVariant> SemanticMemento::extractedData()
{
    if (!m_pendingStructuredData.isEmpty()) {
        m_postProc.process(m_pendingStructuredData);
        m_pendingStructuredData.clear();
    }
    const auto res = m_postProc.result();
    m_expanded.resize(res.size());
    return res;
}

QVector<bool> SemanticMemento::expanded() const
{
    return m_expanded;
}

void SemanticMemento::toggleExpanded(int index)
{
    if (index >= m_expanded.size()) {
        return;
    }
    m_expanded[index] = !m_expanded.at(index);
}

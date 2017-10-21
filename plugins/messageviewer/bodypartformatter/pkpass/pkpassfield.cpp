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

#include "pkpassfield.h"
#include "pkpassfile.h"

#include <QJsonObject>

PkPassField::PkPassField() = default;

PkPassField::PkPassField(const QJsonObject& obj, const PkPassFile *file)
{
    m_label = file->message(obj.value(QLatin1String("label")).toString());
    m_value = file->message(obj.value(QLatin1String("value")).toString());
}

PkPassField::~PkPassField() = default;

QString PkPassField::label() const
{
    return m_label;
}

QString PkPassField::value() const
{
    return m_value;
}

/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "grammalecteparser.h"
#include "grammalecteplugin_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

GrammalecteParser::GrammalecteParser()
{

}

GrammalecteParser::~GrammalecteParser()
{

}

QVector<GrammalecteInfo> GrammalecteParser::parseResult(const QJsonObject &obj) const
{
    QVector<GrammalecteInfo> infos;
    QJsonArray array = obj.value(QLatin1String("data")).toArray();
    for (const QJsonValue &current : array) {
        if (current.type() == QJsonValue::Object) {
            const QJsonObject grammaObject = current.toObject();
            GrammalecteInfo info;
            info.parse(grammaObject);
            if (info.isValid()) {
                infos.append(info);
            }
        } else {
            qCWarning(KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG) << "Problem when parsing grammalecte result" << current;
        }
    }
    return infos;
}

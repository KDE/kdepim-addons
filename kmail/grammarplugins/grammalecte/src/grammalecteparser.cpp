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
#include "libgrammalecte_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

GrammalecteParser::GrammalecteParser()
{
}

GrammalecteParser::~GrammalecteParser()
{
}

QVector<GrammarError> GrammalecteParser::parseResult(const QJsonObject &obj) const
{
    QVector<GrammarError> infos;
    if (!obj.contains(QLatin1String("grammalecte"))) {
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "Error in json " << obj;
        return infos;
    }
    const QJsonArray array = obj.value(QLatin1String("data")).toArray();
    for (const QJsonValue &current : array) {
        if (current.type() == QJsonValue::Object) {
            //Check lGrammarErrors
            const QJsonObject grammaObject = current.toObject();
            const int blockId = grammaObject.value(QStringLiteral("iParagraph")).toInt();
            //qDebug() << " blockId " << blockId;
            const QJsonArray grammarErrorArray = grammaObject.value(QLatin1String("lGrammarErrors")).toArray();
            for (const QJsonValue &error : grammarErrorArray) {
                //qDebug() << " grammarErrorArray"<<error;
                GrammalecteGrammarError info;
                if (error.type() == QJsonValue::Object) {
                    info.parse(error.toObject(), blockId);
                    if (info.isValid()) {
                        infos.append(info);
                    }
                } else {
                    qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "Problem when parsing grammalecte error" << error;
                }
            }
        } else {
            qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "Problem when parsing grammalecte result" << current;
        }
    }
    return infos;
}

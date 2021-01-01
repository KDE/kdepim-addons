/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteparser.h"
#include "libgrammalecte_debug.h"
#include <QJsonArray>
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

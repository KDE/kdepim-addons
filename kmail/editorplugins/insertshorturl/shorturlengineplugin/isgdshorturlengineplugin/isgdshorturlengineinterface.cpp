/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#include "isgdshorturlengineinterface.h"
#include "isgdshorturlengineplugin_debug.h"

#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "../../shorturlengineplugin/shorturlengineplugin.h"

IsgdShortUrlEngineInterface::IsgdShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent)
    : ShortUrlEngineInterface(plugin, parent)
{
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &IsgdShortUrlEngineInterface::slotShortUrlFinished);
}

IsgdShortUrlEngineInterface::~IsgdShortUrlEngineInterface()
{
}

QString IsgdShortUrlEngineInterface::engineName() const
{
    return mEnginePlugin->engineName();
}

void IsgdShortUrlEngineInterface::generateShortUrl()
{
    const QString requestUrl = QStringLiteral("https://is.gd/create.php?%1&url=%2").arg(QStringLiteral("format=json"), mOriginalUrl);
    QNetworkRequest request = QNetworkRequest(QUrl(requestUrl));

    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
    QNetworkReply *reply = mNetworkAccessManager->get(request);
    connect(reply, qOverload<QNetworkReply::NetworkError>(&QNetworkReply::error), this, &IsgdShortUrlEngineInterface::slotErrorFound);
}

void IsgdShortUrlEngineInterface::slotSslErrors(QNetworkReply *reply, const QList<QSslError> &error)
{
    reply->ignoreSslErrors(error);
}

void IsgdShortUrlEngineInterface::slotShortUrlFinished(QNetworkReply *reply)
{
    if (mErrorFound) {
        return;
    }

    const QByteArray data = reply->readAll();
    QJsonParseError error;
    const QJsonDocument json = QJsonDocument::fromJson(data, &error);
    qCDebug(ISGDSHORTURLENGINEPLUGIN_LOG) << "void IsGdShortUrl::slotShortUrlFinished(QNetworkReply *reply) " << data;

    reply->deleteLater();

    if (error.error != QJsonParseError::NoError || json.isNull()) {
        qCDebug(ISGDSHORTURLENGINEPLUGIN_LOG) << " Error during parsing" << error.errorString();
        Q_EMIT shortUrlFailed(error.errorString());
        return;
    }
    const QMap<QString, QVariant> map = json.toVariant().toMap();

    const QVariant var = map.value(QStringLiteral("shorturl"));
    if (var.isValid()) {
        mTextCursor.insertText(var.toString());
    }
}

/*
   Copyright (C) 2015-2018 Montel Laurent <montel@kde.org>

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

#include "ur1cashorturlengineinterface.h"
#include "../shorturlengineplugin.h"
#include "ur1cashorturlengineplugin_debug.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>

Ur1CaShortUrlEngineInterface::Ur1CaShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent)
    : ShortUrlEngineInterface(plugin, parent)
{
    connect(mNetworkAccessManager, &QNetworkAccessManager::sslErrors, this, &Ur1CaShortUrlEngineInterface::slotSslErrors);
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &Ur1CaShortUrlEngineInterface::slotShortUrlFinished);
}

Ur1CaShortUrlEngineInterface::~Ur1CaShortUrlEngineInterface()
{
}

QString Ur1CaShortUrlEngineInterface::engineName() const
{
    return mEnginePlugin->engineName();
}

void Ur1CaShortUrlEngineInterface::generateShortUrl()
{
    QUrl url(QStringLiteral("http://ur1.ca/"));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("longurl"), mOriginalUrl);

    url.setQuery(query);
    QByteArray postData;

    postData = query.query().toLatin1();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("text/plain"));

    QNetworkReply *reply = mNetworkAccessManager->post(request, postData);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &Ur1CaShortUrlEngineInterface::slotErrorFound);
}

void Ur1CaShortUrlEngineInterface::slotSslErrors(QNetworkReply *reply, const QList<QSslError> &error)
{
    reply->ignoreSslErrors(error);
}

void Ur1CaShortUrlEngineInterface::slotShortUrlFinished(QNetworkReply *reply)
{
    if (mErrorFound) {
        reply->deleteLater();
        return;
    }
    QString output = QLatin1String(reply->readAll());
    qCDebug(UR1CASHORTURLENGINEPLUGIN_LOG) << "void Ur1CaShortUrl::slotShortUrlFinished(QNetworkReply *reply) " << output;
    QRegExp rx(QStringLiteral("<p class=[\'\"]success[\'\"]>(.*)</p>"));
    rx.setMinimal(true);
    output = rx.cap(1);
    rx.setPattern(QStringLiteral("href=[\'\"](.*)[\'\"]"));
    rx.indexIn(output);
    output = rx.cap(1);
    qCDebug(UR1CASHORTURLENGINEPLUGIN_LOG) << "Short url is: " << output;
    if (!output.isEmpty()) {
        mTextCursor.insertText(output);
    } else {
        Q_EMIT shortUrlFailed(QString());
    }
    reply->deleteLater();
}

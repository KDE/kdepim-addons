/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    connect(reply, qOverload<QNetworkReply::NetworkError>(&QNetworkReply::error), this, &Ur1CaShortUrlEngineInterface::slotErrorFound);
}

void Ur1CaShortUrlEngineInterface::slotSslErrors(QNetworkReply *reply, const QList<QSslError> &error)
{
    reply->ignoreSslErrors(error);
}

void Ur1CaShortUrlEngineInterface::slotShortUrlFinished(QNetworkReply *reply)
{
    if (!mErrorFound) {
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
    }
    reply->deleteLater();
}

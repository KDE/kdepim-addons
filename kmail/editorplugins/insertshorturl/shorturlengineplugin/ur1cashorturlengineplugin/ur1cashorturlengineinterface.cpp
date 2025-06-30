/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ur1cashorturlengineinterface.h"
using namespace Qt::Literals::StringLiterals;

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
    QUrl url(u"http://ur1.ca/"_s);
    QUrlQuery query;
    query.addQueryItem(u"longurl"_s, mOriginalUrl);

    url.setQuery(query);
    QByteArray postData;

    postData = query.query().toLatin1();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, u"text/plain"_s);

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
        QString output = QLatin1StringView(reply->readAll());
        qCDebug(UR1CASHORTURLENGINEPLUGIN_LOG) << "void Ur1CaShortUrl::slotShortUrlFinished(QNetworkReply *reply) " << output;
        QRegExp rx(u"<p class=[\'\"]success[\'\"]>(.*)</p>"_s);
        rx.setMinimal(true);
        output = rx.cap(1);
        rx.setPattern(u"href=[\'\"](.*)[\'\"]"_s);
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

#include "moc_ur1cashorturlengineinterface.cpp"

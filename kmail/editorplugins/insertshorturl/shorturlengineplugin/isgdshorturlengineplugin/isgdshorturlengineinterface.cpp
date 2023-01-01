/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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

IsgdShortUrlEngineInterface::~IsgdShortUrlEngineInterface() = default;

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
    connect(reply, qOverload<QNetworkReply::NetworkError>(&QNetworkReply::errorOccurred), this, &IsgdShortUrlEngineInterface::slotErrorFound);
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

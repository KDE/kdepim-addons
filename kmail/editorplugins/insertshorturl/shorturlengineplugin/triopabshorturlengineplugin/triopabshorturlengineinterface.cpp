/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "triopabshorturlengineinterface.h"
#include "../shorturlengineplugin.h"

#include <QNetworkReply>
#include <QNetworkRequest>

TripAbShortUrlEngineInterface::TripAbShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent)
    : ShortUrlEngineInterface(plugin, parent)
{
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &TripAbShortUrlEngineInterface::slotShortUrlFinished);
}

TripAbShortUrlEngineInterface::~TripAbShortUrlEngineInterface()
{
}

QString TripAbShortUrlEngineInterface::engineName() const
{
    return mEnginePlugin->engineName();
}

void TripAbShortUrlEngineInterface::generateShortUrl()
{
    const QString requestUrl = QStringLiteral("https://to.ly/api.php?longurl=%1").arg(mOriginalUrl);
    QNetworkReply *reply = mNetworkAccessManager->get(QNetworkRequest(QUrl(requestUrl)));
    connect(reply, qOverload<QNetworkReply::NetworkError>(&QNetworkReply::error), this, &TripAbShortUrlEngineInterface::slotErrorFound);
}

void TripAbShortUrlEngineInterface::slotShortUrlFinished(QNetworkReply *reply)
{
    if (!mErrorFound) {
        const QString data = QString::fromUtf8(reply->readAll());
        if (!data.isEmpty()) {
            mTextCursor.insertText(data);
        }
    }
    reply->deleteLater();
}

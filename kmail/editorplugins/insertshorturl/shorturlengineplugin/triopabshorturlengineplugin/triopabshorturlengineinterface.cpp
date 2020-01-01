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

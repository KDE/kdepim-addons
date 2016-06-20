/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "tinyurlengineinterface.h"
#include "../shorturlengineplugin.h"
#include <KLocalizedString>

#include <QNetworkAccessManager>

TinyUrlEngineInterface::TinyUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent)
    : ShortUrlEngineInterface(plugin, parent)
{
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &TinyUrlEngineInterface::slotShortUrlFinished);
}

TinyUrlEngineInterface::~TinyUrlEngineInterface()
{

}

QString TinyUrlEngineInterface::engineName() const
{
    return mEnginePlugin->engineName();
}

void TinyUrlEngineInterface::generateShortUrl()
{
    const QString requestUrl = QStringLiteral("http://tinyurl.com/api-create.php?url=%1").arg(mOriginalUrl);
    QNetworkReply *reply = mNetworkAccessManager->get(QNetworkRequest(QUrl(requestUrl)));
    connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &TinyUrlEngineInterface::slotErrorFound);
}

void TinyUrlEngineInterface::slotShortUrlFinished(QNetworkReply *reply)
{
    if (!mErrorFound) {
        const QString data = QString::fromUtf8(reply->readAll());
        if (!data.isEmpty()) {
            Q_EMIT shortUrlGenerated(data);
        }
    }
    reply->deleteLater();
}

void TinyUrlEngineInterface::slotErrorFound(QNetworkReply::NetworkError error)
{
    mErrorFound = true;
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    Q_EMIT shortUrlFailed(i18n("Error reported by server:\n\'%1\'", (reply ? reply->errorString() : QString::number(error))));
}

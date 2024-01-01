/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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

TinyUrlEngineInterface::~TinyUrlEngineInterface() = default;

QString TinyUrlEngineInterface::engineName() const
{
    return mEnginePlugin->engineName();
}

void TinyUrlEngineInterface::generateShortUrl()
{
    const QString requestUrl = QStringLiteral("https://tinyurl.com/api-create.php?url=%1").arg(mOriginalUrl);
    QNetworkReply *reply = mNetworkAccessManager->get(QNetworkRequest(QUrl(requestUrl)));
    connect(reply, &QNetworkReply::errorOccurred, this, &TinyUrlEngineInterface::slotErrorFound);
}

void TinyUrlEngineInterface::slotShortUrlFinished(QNetworkReply *reply)
{
    if (!mErrorFound) {
        const QString data = QString::fromUtf8(reply->readAll());
        if (!data.isEmpty()) {
            mTextCursor.insertText(data);
        }
    }
    reply->deleteLater();
}

void TinyUrlEngineInterface::slotErrorFound(QNetworkReply::NetworkError error)
{
    mErrorFound = true;
    auto reply = qobject_cast<QNetworkReply *>(sender());
    Q_EMIT shortUrlFailed(i18n("Error reported by server:\n\'%1\'", (reply ? reply->errorString() : QString::number(error))));
}

#include "moc_tinyurlengineinterface.cpp"

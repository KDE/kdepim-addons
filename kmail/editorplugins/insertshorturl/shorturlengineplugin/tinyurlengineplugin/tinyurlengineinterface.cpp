/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "tinyurlengineinterface.h"
using namespace Qt::Literals::StringLiterals;

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
    const QString requestUrl = u"https://tinyurl.com/api-create.php?url=%1"_s.arg(mOriginalUrl);
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

#include "moc_tinyurlengineinterface.cpp"

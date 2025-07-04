/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shorturlengineinterface.h"
using namespace Qt::Literals::StringLiterals;

#include "shorturlengineplugin.h"

#include <KLocalizedString>

#include <QNetworkAccessManager>

ShortUrlEngineInterface::ShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
    , mEnginePlugin(plugin)
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
}

ShortUrlEngineInterface::~ShortUrlEngineInterface() = default;

void ShortUrlEngineInterface::slotErrorFound(QNetworkReply::NetworkError error)
{
    mErrorFound = true;
    auto reply = qobject_cast<QNetworkReply *>(sender());
    Q_EMIT shortUrlFailed(i18n("Error reported by server:\n\'%1\'", (reply ? reply->errorString() : QString::number(error))));
}

void ShortUrlEngineInterface::setShortUrl(const QString &url)
{
    mErrorFound = false;
    if (!url.trimmed().startsWith(QLatin1StringView("http://")) && !url.trimmed().startsWith(QLatin1StringView("https://"))
        && !url.trimmed().startsWith(QLatin1StringView("ftp://")) && !url.trimmed().startsWith(QLatin1StringView("ftps://"))) {
        mOriginalUrl = QLatin1StringView("http://") + url;
    } else {
        mOriginalUrl = url;
    }
}

QString ShortUrlEngineInterface::pluginName() const
{
    return mEnginePlugin->pluginName();
}

void ShortUrlEngineInterface::setTextCursor(const QTextCursor &cursor)
{
    mTextCursor = cursor;
}

#include "moc_shorturlengineinterface.cpp"

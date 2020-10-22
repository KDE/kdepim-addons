/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgetlistoflanguagejob.h"
#include "liblanguagetool_debug.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

LanguageToolGetListOfLanguageJob::LanguageToolGetListOfLanguageJob(QObject *parent)
    : QObject(parent)
{
}

LanguageToolGetListOfLanguageJob::~LanguageToolGetListOfLanguageJob()
{
}

bool LanguageToolGetListOfLanguageJob::canStart() const
{
    if (!mNetworkAccessManager || mUrl.isEmpty()) {
        return false;
    }
    return true;
}

void LanguageToolGetListOfLanguageJob::start()
{
    if (!canStart()) {
        qCWarning(LIBLANGUAGE_PLUGIN_LOG) << "Impossible to start LanguageToolGetListOfLanguageJob";
        deleteLater();
        return;
    }
    QNetworkRequest request(QUrl::fromUserInput(mUrl));
    addRequestAttribute(request);
    QNetworkReply *reply = mNetworkAccessManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &LanguageToolGetListOfLanguageJob::slotCheckListOfLanguagesFinished);
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &LanguageToolGetListOfLanguageJob::slotFinish);
}

void LanguageToolGetListOfLanguageJob::slotFinish(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qCWarning(LIBLANGUAGE_PLUGIN_LOG) << " Error reply - "<<reply->errorString();
        Q_EMIT error(reply->errorString());
    }
}

void LanguageToolGetListOfLanguageJob::slotCheckListOfLanguagesFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        const QByteArray data = reply->readAll();
        Q_EMIT finished(QString::fromUtf8(data));
        reply->deleteLater();
    }
    deleteLater();
}

void LanguageToolGetListOfLanguageJob::addRequestAttribute(QNetworkRequest &request) const
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
}

QString LanguageToolGetListOfLanguageJob::listOfLanguagePath() const
{
    return mListOfLanguagePath;
}

void LanguageToolGetListOfLanguageJob::setListOfLanguagePath(const QString &getListOfLanguagePath)
{
    mListOfLanguagePath = getListOfLanguagePath;
}

QNetworkAccessManager *LanguageToolGetListOfLanguageJob::networkAccessManager() const
{
    return mNetworkAccessManager;
}

void LanguageToolGetListOfLanguageJob::setNetworkAccessManager(QNetworkAccessManager *networkAccessManager)
{
    mNetworkAccessManager = networkAccessManager;
}

QString LanguageToolGetListOfLanguageJob::url() const
{
    return mUrl;
}

void LanguageToolGetListOfLanguageJob::setUrl(const QString &url)
{
    mUrl = url;
}

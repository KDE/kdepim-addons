/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolresultjob.h"
#include "liblanguagetool_debug.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

LanguageToolResultJob::LanguageToolResultJob(QObject *parent)
    : QObject(parent)
{
}

LanguageToolResultJob::~LanguageToolResultJob() = default;

static bool hasNotEmptyText(const QString &text)
{
    for (int i = 0; i < text.length(); ++i) {
        if (!text.at(i).isSpace()) {
            return true;
        }
    }
    return false;
}

bool LanguageToolResultJob::canStart() const
{
    return canStartError() == LanguageToolResultJob::JobError::NotError;
}

LanguageToolResultJob::JobError LanguageToolResultJob::canStartError() const
{
    if (!mNetworkAccessManager) {
        return LanguageToolResultJob::JobError::NetworkManagerNotDefined;
    }
    if (!hasNotEmptyText(mText)) {
        return LanguageToolResultJob::JobError::EmptyText;
    }
    if (mUrl.isEmpty()) {
        return LanguageToolResultJob::JobError::UrlNotDefined;
    }
    if (mLanguage.isEmpty()) {
        return LanguageToolResultJob::JobError::LanguageNotDefined;
    }
    return LanguageToolResultJob::JobError::NotError;
}

void LanguageToolResultJob::start()
{
    const LanguageToolResultJob::JobError errorType = canStartError();
    switch (errorType) {
    case LanguageToolResultJob::JobError::EmptyText:
        return;
    case LanguageToolResultJob::JobError::UrlNotDefined:
    case LanguageToolResultJob::JobError::NetworkManagerNotDefined:
    case LanguageToolResultJob::JobError::LanguageNotDefined:
        qCWarning(LIBLANGUAGE_PLUGIN_LOG) << "Impossible to start language tool";
        return;
    case LanguageToolResultJob::JobError::NotError:
        break;
    }
    QNetworkRequest request(QUrl::fromUserInput(mUrl));
    addRequestAttribute(request);
    const QByteArray ba = "text=" + mText.toUtf8() + "&language=" + mLanguage.toLatin1();
    QNetworkReply *reply = mNetworkAccessManager->post(request, ba);
    connect(reply, &QNetworkReply::finished, this, &LanguageToolResultJob::slotCheckGrammarFinished);
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &LanguageToolResultJob::slotFinish);
}

void LanguageToolResultJob::slotFinish(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qCWarning(LIBLANGUAGE_PLUGIN_LOG) << " Error reply - " << reply->errorString();
        Q_EMIT error(reply->errorString());
    }
}

void LanguageToolResultJob::slotCheckGrammarFinished()
{
    auto reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        const QByteArray data = reply->readAll();
        Q_EMIT finished(QString::fromUtf8(data));
        reply->deleteLater();
    }
    deleteLater();
}

void LanguageToolResultJob::addRequestAttribute(QNetworkRequest &request) const
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));
}

QString LanguageToolResultJob::language() const
{
    return mLanguage;
}

void LanguageToolResultJob::setLanguage(const QString &language)
{
    mLanguage = language;
}

QString LanguageToolResultJob::url() const
{
    return mUrl;
}

void LanguageToolResultJob::setUrl(const QString &url)
{
    mUrl = url;
}

QStringList LanguageToolResultJob::arguments() const
{
    return mArguments;
}

void LanguageToolResultJob::setArguments(const QStringList &arguments)
{
    mArguments = arguments;
}

QNetworkAccessManager *LanguageToolResultJob::networkAccessManager() const
{
    return mNetworkAccessManager;
}

void LanguageToolResultJob::setNetworkAccessManager(QNetworkAccessManager *networkAccessManager)
{
    mNetworkAccessManager = networkAccessManager;
}

QString LanguageToolResultJob::text() const
{
    return mText;
}

void LanguageToolResultJob::setText(const QString &text)
{
    mText = text;
}

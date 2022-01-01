/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libkmaillanguagetool_export.h"
#include <QNetworkRequest>
#include <QObject>
class QNetworkAccessManager;
class QNetworkReply;
class LIBKMAILLANGUAGETOOL_EXPORT LanguageToolGetListOfLanguageJob : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolGetListOfLanguageJob(QObject *parent = nullptr);
    ~LanguageToolGetListOfLanguageJob() override;

    Q_REQUIRED_RESULT bool canStart() const;
    void start();

    Q_REQUIRED_RESULT QString listOfLanguagePath() const;
    void setListOfLanguagePath(const QString &listOfLanguagePath);

    QNetworkAccessManager *networkAccessManager() const;
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);

    Q_REQUIRED_RESULT QString url() const;
    void setUrl(const QString &url);

Q_SIGNALS:
    void finished(const QString &result);
    void error(const QString &errorStr);

private:
    Q_DISABLE_COPY(LanguageToolGetListOfLanguageJob)
    void addRequestAttribute(QNetworkRequest &request) const;
    void slotCheckListOfLanguagesFinished();
    void slotFinish(QNetworkReply *reply);

    QString mListOfLanguagePath;
    QNetworkAccessManager *mNetworkAccessManager = nullptr;
    QString mUrl;
};


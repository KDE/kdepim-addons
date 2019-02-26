/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#ifndef LANGUAGETOOLGETLISTOFLANGUAGEJOB_H
#define LANGUAGETOOLGETLISTOFLANGUAGEJOB_H

#include <QNetworkRequest>
#include <QObject>
#include "libkmaillanguagetool_export.h"
class QNetworkAccessManager;
class QNetworkReply;
class LIBKMAILLANGUAGETOOL_EXPORT LanguageToolGetListOfLanguageJob : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolGetListOfLanguageJob(QObject *parent = nullptr);
    ~LanguageToolGetListOfLanguageJob();

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

#endif // LANGUAGETOOLGETLISTOFLANGUAGEJOB_H

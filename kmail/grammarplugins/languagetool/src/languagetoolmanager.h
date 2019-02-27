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

#ifndef LANGUAGETOOLMANAGER_H
#define LANGUAGETOOLMANAGER_H

#include <QObject>
#include "libkmaillanguagetool_export.h"
class QNetworkAccessManager;
class LIBKMAILLANGUAGETOOL_EXPORT LanguageToolManager : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolManager(QObject *parent = nullptr);
    ~LanguageToolManager();
    static LanguageToolManager *self();

    QNetworkAccessManager *networkAccessManager() const;

    Q_REQUIRED_RESULT QString languageToolPath() const;
    void setLanguageToolPath(const QString &path);

    void loadSettings();
    void saveSettings();

    Q_REQUIRED_RESULT QString language() const;
    void setLanguage(const QString &language);

    Q_REQUIRED_RESULT bool useLocalInstance() const;
    void setUseLocalInstance(bool useLocalInstance);

    Q_REQUIRED_RESULT QString languageToolCheckPath() const;

    Q_REQUIRED_RESULT QString languageToolLanguagesPath() const;

    static QString convertToLanguagePath(const QString &path);
private:
    Q_DISABLE_COPY(LanguageToolManager)
    QString mLanguage;
    QString mLanguageToolPath;
    QNetworkAccessManager *mNetworkAccessManager = nullptr;
    bool mUseLocalInstance = false;
};

#endif // LANGUAGETOOLMANAGER_H

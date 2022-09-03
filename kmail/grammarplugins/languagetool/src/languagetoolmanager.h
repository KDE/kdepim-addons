/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libkmaillanguagetool_export.h"
#include <QHash>
#include <QObject>
class QColor;
class QNetworkAccessManager;
class LIBKMAILLANGUAGETOOL_EXPORT LanguageToolManager : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolManager(QObject *parent = nullptr);
    ~LanguageToolManager() override;
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

    Q_REQUIRED_RESULT static QString convertToLanguagePath(const QString &path);

    Q_REQUIRED_RESULT QColor grammarColorForError(const QString &error);

    Q_REQUIRED_RESULT bool allowToGetListOfLanguages() const;

private:
    Q_DISABLE_COPY(LanguageToolManager)
    QHash<QString, QColor> mGrammarColor;
    QString mLanguage;
    QString mLanguageToolPath;
    QNetworkAccessManager *const mNetworkAccessManager;
    bool mUseLocalInstance = false;
};

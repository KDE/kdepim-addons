/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLMANAGER_H
#define LANGUAGETOOLMANAGER_H

#include <QObject>
#include <QHash>
#include "libkmaillanguagetool_export.h"
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

    static QString convertToLanguagePath(const QString &path);

    Q_REQUIRED_RESULT QColor grammarColorForError(const QString &error);
private:
    Q_DISABLE_COPY(LanguageToolManager)
    QHash<QString, QColor> mGrammarColor;
    QString mLanguage;
    QString mLanguageToolPath;
    QNetworkAccessManager *const mNetworkAccessManager;
    bool mUseLocalInstance = false;
};

#endif // LANGUAGETOOLMANAGER_H

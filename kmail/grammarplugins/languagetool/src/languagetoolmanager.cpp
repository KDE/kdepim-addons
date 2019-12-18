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

#include "languagetoolmanager.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QNetworkAccessManager>
#include <QColor>
#include <QRandomGenerator>

LanguageToolManager::LanguageToolManager(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    loadSettings();
}

LanguageToolManager::~LanguageToolManager()
{
}

LanguageToolManager *LanguageToolManager::self()
{
    static LanguageToolManager s_self;
    return &s_self;
}

QNetworkAccessManager *LanguageToolManager::networkAccessManager() const
{
    return mNetworkAccessManager;
}

QString LanguageToolManager::languageToolCheckPath() const
{
    if (mLanguageToolPath.isEmpty()) {
        return {};
    }
    return mLanguageToolPath + QStringLiteral("/check");
}

QString LanguageToolManager::languageToolLanguagesPath() const
{
    if (mLanguageToolPath.isEmpty()) {
        return {};
    }
    return convertToLanguagePath(mLanguageToolPath);
}

QString LanguageToolManager::convertToLanguagePath(const QString &path)
{
    return path + QStringLiteral("/languages");
}

QColor LanguageToolManager::grammarColorForError(const QString &error)
{
    QColor col = mGrammarColor.value(error);
    if (col.isValid()) {
        return col;
    }
    col.setRgb(QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256));
    //Generate color.
    mGrammarColor.insert(error, col);
    return col;
}

QString LanguageToolManager::languageToolPath() const
{
    return mLanguageToolPath;
}

void LanguageToolManager::setLanguageToolPath(const QString &path)
{
    mLanguageToolPath = path;
}

void LanguageToolManager::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "LanguageTool");
    mLanguageToolPath = grp.readEntry(QStringLiteral("languagetoolpath"), QStringLiteral("https://languagetool.org/api/v2"));
    mLanguage = grp.readEntry(QStringLiteral("language"), QStringLiteral("en"));
    mUseLocalInstance = grp.readEntry(QStringLiteral("useLocalInstance"), false);
    //TODO add options ?
}

void LanguageToolManager::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "LanguageTool");
    grp.writeEntry(QStringLiteral("languagetoolpath"), mLanguageToolPath);
    grp.writeEntry(QStringLiteral("language"), mLanguage);
    grp.writeEntry(QStringLiteral("useLocalInstance"), mUseLocalInstance);
}

QString LanguageToolManager::language() const
{
    return mLanguage;
}

void LanguageToolManager::setLanguage(const QString &language)
{
    mLanguage = language;
}

bool LanguageToolManager::useLocalInstance() const
{
    return mUseLocalInstance;
}

void LanguageToolManager::setUseLocalInstance(bool useLocalInstance)
{
    mUseLocalInstance = useLocalInstance;
}

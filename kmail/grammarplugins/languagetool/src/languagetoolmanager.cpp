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

LanguagetoolManager::LanguagetoolManager(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    loadSettings();
}

LanguagetoolManager::~LanguagetoolManager()
{

}

LanguagetoolManager *LanguagetoolManager::self()
{
    static LanguagetoolManager s_self;
    return &s_self;
}

QNetworkAccessManager *LanguagetoolManager::networkAccessManager() const
{
    return mNetworkAccessManager;
}

QString LanguagetoolManager::languageToolPath() const
{
    return mLanguageToolPath;
}

void LanguagetoolManager::setLanguageToolPath(const QString &path)
{
    mLanguageToolPath = path;
}

void LanguagetoolManager::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "LanguageTool");
    mLanguageToolPath = grp.readEntry(QStringLiteral("languagetoolpath"), QStringLiteral("https://languagetool.org/api/v2/check"));
    mLanguage = grp.readEntry(QStringLiteral("language"), QStringLiteral("en"));
}

void LanguagetoolManager::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "LanguageTool");
    grp.writeEntry(QStringLiteral("languagetoolpath"), mLanguageToolPath);
    grp.writeEntry(QStringLiteral("language"), mLanguage);
}

QString LanguagetoolManager::language() const
{
    return mLanguage;
}

void LanguagetoolManager::setLanguage(const QString &language)
{
    mLanguage = language;
}

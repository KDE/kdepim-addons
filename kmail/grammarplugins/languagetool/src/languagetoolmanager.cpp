/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolmanager.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QNetworkAccessManager>
#include <QColor>
#include <QRandomGenerator>
namespace {
static const char myConfigGroupName[] = "LanguageTool";
}
LanguageToolManager::LanguageToolManager(QObject *parent)
    : QObject(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
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
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    mLanguageToolPath = grp.readEntry(QStringLiteral("languagetoolpath"), QStringLiteral("https://languagetool.org/api/v2"));
    mLanguage = grp.readEntry(QStringLiteral("language"), QStringLiteral("en"));
    mUseLocalInstance = grp.readEntry(QStringLiteral("useLocalInstance"), false);
    //TODO add options ?
}

void LanguageToolManager::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
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

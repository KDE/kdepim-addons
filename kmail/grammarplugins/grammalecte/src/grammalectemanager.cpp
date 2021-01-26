/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectemanager.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QStandardPaths>
namespace
{
static const char myConfigGroupName[] = "Grammalecte";
}
GrammalecteManager::GrammalecteManager(QObject *parent)
    : QObject(parent)
{
    loadSettings();
}

GrammalecteManager::~GrammalecteManager()
{
}

GrammalecteManager *GrammalecteManager::self()
{
    static GrammalecteManager s_self;
    return &s_self;
}

void GrammalecteManager::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    grp.writeEntry(QStringLiteral("pythonpath"), mPythonPath);
    grp.writeEntry(QStringLiteral("grammalectepath"), mGrammalectePath);
    grp.writeEntry(QStringLiteral("options"), mOptions);
}

QStringList GrammalecteManager::options() const
{
    return mOptions;
}

void GrammalecteManager::setOptions(const QStringList &saveOptions)
{
    mOptions = saveOptions;
}

void GrammalecteManager::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    mPythonPath = grp.readEntry(QStringLiteral("pythonpath"));
    if (mPythonPath.isEmpty()) {
        mPythonPath = QStandardPaths::findExecutable(QStringLiteral("python3"));
    }
    mGrammalectePath = grp.readEntry(QStringLiteral("grammalectepath"));
    mOptions = grp.readEntry(QStringLiteral("options"), QStringList());
}

QString GrammalecteManager::pythonPath() const
{
    return mPythonPath;
}

QString GrammalecteManager::grammalectePath() const
{
    return mGrammalectePath;
}

void GrammalecteManager::setPythonPath(const QString &pythonPath)
{
    mPythonPath = pythonPath;
}

void GrammalecteManager::setGrammalectePath(const QString &grammalectePath)
{
    mGrammalectePath = grammalectePath;
}

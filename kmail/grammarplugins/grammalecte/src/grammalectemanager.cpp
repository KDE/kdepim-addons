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


#include "grammalectemanager.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QStandardPaths>

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

void GrammalecteManager::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Grammalecte");
    mPythonPath = grp.readEntry(QStringLiteral("pythonpath"));
    if (mPythonPath.isEmpty()) {
        mPythonPath = QStandardPaths::findExecutable(QStringLiteral("python3"));
    }
    mGrammalectePath = grp.readEntry(QStringLiteral("grammalectepath"));
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

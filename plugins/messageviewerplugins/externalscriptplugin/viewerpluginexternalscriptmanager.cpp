/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptmanager.h"
#include "viewerpluginexternalscriptsloadjob.h"

#include <QStandardPaths>

ViewerPluginExternalScriptManager::ViewerPluginExternalScriptManager(QObject *parent)
    : QObject(parent)
{
    readExternalScriptInfo();
}

ViewerPluginExternalScriptManager::~ViewerPluginExternalScriptManager() = default;

ViewerPluginExternalScriptManager *ViewerPluginExternalScriptManager::self()
{
    static ViewerPluginExternalScriptManager s_self;
    return &s_self;
}

void ViewerPluginExternalScriptManager::readExternalScriptInfo()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList lst =
        QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, QStringLiteral("messageviewerplugins/"), QStandardPaths::LocateDirectory);
    job.setExternalScriptsDirectories(lst);
    job.start();
    mScriptInfos = job.scriptInfos();
}

QVector<ViewerPluginExternalScriptInfo> ViewerPluginExternalScriptManager::scriptInfos() const
{
    return mScriptInfos;
}

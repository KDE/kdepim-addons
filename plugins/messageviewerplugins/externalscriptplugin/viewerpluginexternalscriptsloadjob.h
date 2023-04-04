/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "viewerpluginexternalscriptinfo.h"

#include <QList>
#include <QStringList>
class ViewerPluginExternalScriptsLoadJob
{
public:
    ViewerPluginExternalScriptsLoadJob();
    ~ViewerPluginExternalScriptsLoadJob();

    void start();
    void setExternalScriptsDirectories(const QStringList &dir);
    Q_REQUIRED_RESULT QStringList externalScriptsDirectories() const;
    Q_REQUIRED_RESULT QList<ViewerPluginExternalScriptInfo> scriptInfos() const;

private:
    QList<ViewerPluginExternalScriptInfo> mScriptInfos;
    QStringList mDirectories;
};

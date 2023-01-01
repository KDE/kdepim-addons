/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "viewerpluginexternalscriptinfo.h"

#include <QStringList>
#include <QVector>
class ViewerPluginExternalScriptsLoadJob
{
public:
    ViewerPluginExternalScriptsLoadJob();
    ~ViewerPluginExternalScriptsLoadJob();

    void start();
    void setExternalScriptsDirectories(const QStringList &dir);
    Q_REQUIRED_RESULT QStringList externalScriptsDirectories() const;
    Q_REQUIRED_RESULT QVector<ViewerPluginExternalScriptInfo> scriptInfos() const;

private:
    QVector<ViewerPluginExternalScriptInfo> mScriptInfos;
    QStringList mDirectories;
};

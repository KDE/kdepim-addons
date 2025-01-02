/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

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
    [[nodiscard]] QStringList externalScriptsDirectories() const;
    [[nodiscard]] QList<ViewerPluginExternalScriptInfo> scriptInfos() const;

private:
    QList<ViewerPluginExternalScriptInfo> mScriptInfos;
    QStringList mDirectories;
};

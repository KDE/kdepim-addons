/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "viewerpluginexternalscriptsloadjob.h"
#include "externalscriptplugin_debug.h"

ViewerPluginExternalScriptsLoadJob::ViewerPluginExternalScriptsLoadJob(QObject *parent)
    : QObject(parent)
{

}

ViewerPluginExternalScriptsLoadJob::~ViewerPluginExternalScriptsLoadJob()
{

}

void ViewerPluginExternalScriptsLoadJob::start()
{
    mScriptInfos.clear();
    if (mDirectory.isEmpty()) {
        qCDebug(EXTERNALSCRIPTPLUGIN_LOG) << "External script directory not defined";
    } else {
        //TODO
    }
}

void ViewerPluginExternalScriptsLoadJob::setExternalScriptsDirectory(const QString &dir)
{
    mDirectory = dir;
}

QString ViewerPluginExternalScriptsLoadJob::externalScriptsDirectory() const
{
    return mDirectory;
}

QVector<ViewerPluginExternalScriptInfo> ViewerPluginExternalScriptsLoadJob::scriptInfos() const
{
    return mScriptInfos;
}

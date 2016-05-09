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

#include <KConfig>
#include <KConfigGroup>
#include <QDir>

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
        QDir dir(mDirectory);
        if (dir.exists()) {
            const QDir::Filters filters = QDir::Files | QDir::Hidden | QDir::NoSymLinks;
            const QFileInfoList list = dir.entryInfoList(QStringList() << QStringLiteral("*.desktop"), filters);
            const int listSize(list.size());
            for (int i = 0; i < listSize; ++i) {
                KConfig config(list.at(i).filePath());
                KConfigGroup group(&config, QStringLiteral("Desktop Entry"));
                if (group.isValid()) {
                    ViewerPluginExternalScriptInfo info;
                    info.setName(group.readEntry("Name", QString()));
                    //TODO is valid ?
                    mScriptInfos.append(info);
                }
            }
        }
        //TODO read desktop file
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

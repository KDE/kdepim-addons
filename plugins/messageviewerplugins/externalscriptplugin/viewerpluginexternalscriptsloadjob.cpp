/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "viewerpluginexternalscriptsloadjob.h"
#include "externalscriptplugin_debug.h"

#include <KConfig>
#include <KConfigGroup>
#include <QDir>

ViewerPluginExternalScriptsLoadJob::ViewerPluginExternalScriptsLoadJob()
{

}

ViewerPluginExternalScriptsLoadJob::~ViewerPluginExternalScriptsLoadJob()
{

}

void ViewerPluginExternalScriptsLoadJob::start()
{
    mScriptInfos.clear();
    if (mDirectories.isEmpty()) {
        qCDebug(EXTERNALSCRIPTPLUGIN_LOG) << "External script directory not defined";
    } else {
        Q_FOREACH (const QString &directory, mDirectories) {
            QDir dir(directory);
            if (dir.exists()) {
                const QDir::Filters filters = QDir::Files | QDir::Hidden | QDir::NoSymLinks;
                const QFileInfoList list = dir.entryInfoList(QStringList() << QStringLiteral("*.desktop"), filters);
                const int listSize(list.size());
                QStringList scriptNames;
                for (int i = 0; i < listSize; ++i) {
                    const QString filePath = list.at(i).filePath();

                    KConfig config(filePath);
                    qCDebug(EXTERNALSCRIPTPLUGIN_LOG) << "load file " << filePath;
                    KConfigGroup group(&config, QStringLiteral("Desktop Entry"));
                    if (group.isValid()) {
                        ViewerPluginExternalScriptInfo info;
                        const QString name = group.readEntry("Name", QString());
                        info.setName(name);
                        info.setExecutable(group.readEntry("Executable", QString()));
                        info.setCommandLine(group.readEntry("CommandLine", QString()));
                        info.setDescription(group.readEntry("Description", QString()));
                        info.setIcon(group.readEntry("Icon", QString()));
                        info.setIsReadOnly(!list.at(i).isWritable());
                        info.setFileName(filePath);
                        if (info.isValid()) {
                            mScriptInfos.append(info);
                            if (!scriptNames.contains(name)) {
                                scriptNames.append(name);
                            }
                        }
                    }
                }
            } else {
                qCDebug(EXTERNALSCRIPTPLUGIN_LOG) << "External script directory doesn't exist " << mDirectories;
            }
        }
    }
}

void ViewerPluginExternalScriptsLoadJob::setExternalScriptsDirectories(const QStringList &dir)
{
    mDirectories = dir;
}

QStringList ViewerPluginExternalScriptsLoadJob::externalScriptsDirectories() const
{
    return mDirectories;
}

QVector<ViewerPluginExternalScriptInfo> ViewerPluginExternalScriptsLoadJob::scriptInfos() const
{
    return mScriptInfos;
}

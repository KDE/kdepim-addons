/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptsloadjob.h"
#include "externalscriptplugin_debug.h"

#include <KConfig>
#include <KConfigGroup>
#include <QDir>

ViewerPluginExternalScriptsLoadJob::ViewerPluginExternalScriptsLoadJob() = default;

ViewerPluginExternalScriptsLoadJob::~ViewerPluginExternalScriptsLoadJob() = default;

void ViewerPluginExternalScriptsLoadJob::start()
{
    mScriptInfos.clear();
    if (mDirectories.isEmpty()) {
        qCDebug(EXTERNALSCRIPTPLUGIN_LOG) << "External script directory not defined";
    } else {
        for (const QString &directory : std::as_const(mDirectories)) {
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

QList<ViewerPluginExternalScriptInfo> ViewerPluginExternalScriptsLoadJob::scriptInfos() const
{
    return mScriptInfos;
}

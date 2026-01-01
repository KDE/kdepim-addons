/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptinfo.h"

ViewerPluginExternalScriptInfo::ViewerPluginExternalScriptInfo() = default;

QString ViewerPluginExternalScriptInfo::name() const
{
    return mName;
}

void ViewerPluginExternalScriptInfo::setName(const QString &name)
{
    mName = name;
}

QString ViewerPluginExternalScriptInfo::commandLine() const
{
    return mCommandLine;
}

void ViewerPluginExternalScriptInfo::setCommandLine(const QString &commandLine)
{
    mCommandLine = commandLine;
}

QString ViewerPluginExternalScriptInfo::executable() const
{
    return mExecutable;
}

void ViewerPluginExternalScriptInfo::setExecutable(const QString &executable)
{
    mExecutable = executable;
}

QString ViewerPluginExternalScriptInfo::description() const
{
    return mDescription;
}

void ViewerPluginExternalScriptInfo::setDescription(const QString &description)
{
    mDescription = description;
}

QString ViewerPluginExternalScriptInfo::icon() const
{
    return mIcon;
}

void ViewerPluginExternalScriptInfo::setIcon(const QString &icon)
{
    mIcon = icon;
}

bool ViewerPluginExternalScriptInfo::isValid() const
{
    return !mName.trimmed().isEmpty() && !mExecutable.trimmed().isEmpty();
}

bool ViewerPluginExternalScriptInfo::isReadOnly() const
{
    return mIsReadOnly;
}

void ViewerPluginExternalScriptInfo::setIsReadOnly(bool isReadOnly)
{
    mIsReadOnly = isReadOnly;
}

QString ViewerPluginExternalScriptInfo::fileName() const
{
    return mFileName;
}

void ViewerPluginExternalScriptInfo::setFileName(const QString &fileName)
{
    mFileName = fileName;
}

bool ViewerPluginExternalScriptInfo::operator==(const ViewerPluginExternalScriptInfo &other) const
{
    return (name() == other.name()) && (commandLine() == other.commandLine()) && (executable() == other.executable()) && (description() == other.description())
        && (icon() == other.icon()) && (isReadOnly() == other.isReadOnly()) && (fileName() == other.fileName());
}

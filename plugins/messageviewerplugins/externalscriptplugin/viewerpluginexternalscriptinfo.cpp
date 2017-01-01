/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#include "viewerpluginexternalscriptinfo.h"

ViewerPluginExternalScriptInfo::ViewerPluginExternalScriptInfo()
    : mIsReadOnly(false)
{

}

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
    return !mName.trimmed().isEmpty() &&
           !mExecutable.trimmed().isEmpty();
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
    return (name() == other.name()) &&
           (commandLine() == other.commandLine()) &&
           (executable() == other.executable()) &&
           (description() == other.description()) &&
           (icon() == other.icon()) &&
           (isReadOnly() == other.isReadOnly()) &&
           (fileName() == other.fileName());

}

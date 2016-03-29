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

#include "viewerpluginexternalscriptmanager.h"

class ViewerPluginExternalScriptManagerInstancePrivate
{
public:
    ViewerPluginExternalScriptManagerInstancePrivate()
        : externalScriptPluginManager(new ViewerPluginExternalScriptManager)
    {
    }

    ~ViewerPluginExternalScriptManagerInstancePrivate()
    {
        delete externalScriptPluginManager;
    }

    ViewerPluginExternalScriptManager *externalScriptPluginManager;
};

Q_GLOBAL_STATIC(ViewerPluginExternalScriptManagerInstancePrivate, sInstance)

ViewerPluginExternalScriptManager::ViewerPluginExternalScriptManager(QObject *parent)
    : QObject(parent)
{
    readExternalScriptInfo();
}

ViewerPluginExternalScriptManager::~ViewerPluginExternalScriptManager()
{

}

ViewerPluginExternalScriptManager *ViewerPluginExternalScriptManager::self()
{
    return sInstance->externalScriptPluginManager;
}

void ViewerPluginExternalScriptManager::readExternalScriptInfo()
{
    //TODO
}

QVector<ViewerPluginExternalScriptInfo> ViewerPluginExternalScriptManager::scriptInfos() const
{
    return mScriptInfos;
}

//TODO read list of external script.
//TODO read desktop file.
//TODO read specific directory.

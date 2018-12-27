/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

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

#include "grantleeheaderstyleinterface.h"
#include "messageviewer/headerstyleplugin.h"
#include "messageviewer/headerstyle.h"
#include <grantleetheme/grantleethememanager.h>
#include <KToggleAction>

using namespace MessageViewer;
GrantleeHeaderStyleInterface::GrantleeHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
    , mThemeManager(nullptr)
{
}

GrantleeHeaderStyleInterface::~GrantleeHeaderStyleInterface()
{
    if (mThemeManager) {
        mThemeManager->setThemeMenu(nullptr);
        mThemeManager->setActionGroup(nullptr);
    }
}

void GrantleeHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    mThemeManager = new GrantleeTheme::ThemeManager(QStringLiteral("mail"),
                                                    QStringLiteral("header.desktop"), ac,
                                                    QStringLiteral("messageviewer/themes/"), this);
    mThemeManager->setDownloadNewStuffConfigFile(QStringLiteral("messageviewer_header_themes.knsrc"));
    connect(mThemeManager, &GrantleeTheme::ThemeManager::grantleeThemeSelected, this, &GrantleeHeaderStyleInterface::slotGrantleeHeaders);
    connect(mThemeManager, &GrantleeTheme::ThemeManager::updateThemes, this, &HeaderStyleInterface::styleUpdated);

    mThemeManager->setActionGroup(actionGroup);
    mThemeManager->setThemeMenu(menu);
    const QString themeName = mThemeManager->configuredThemeName();
    mHeaderStylePlugin->headerStyle()->setTheme(mThemeManager->theme(themeName));
    addActionToMenu(menu, actionGroup);
}

void GrantleeHeaderStyleInterface::activateAction()
{
    KToggleAction *act = mThemeManager->actionForTheme();
    if (act) {
        act->setChecked(true);
    }
}

void GrantleeHeaderStyleInterface::slotGrantleeHeaders()
{
    const QString themeName = mThemeManager->configuredThemeName();
    mHeaderStylePlugin->headerStyle()->setTheme(mThemeManager->theme(themeName));
    slotStyleChanged();
}

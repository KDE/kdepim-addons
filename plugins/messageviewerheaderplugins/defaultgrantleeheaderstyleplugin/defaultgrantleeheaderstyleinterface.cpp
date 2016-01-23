/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "defaultgrantleeheaderstyleinterface.h"
#include "messageviewer/headerstyleplugin.h"
#include "messageviewer/headerstyle.h"
#include <grantleetheme/grantleethememanager.h>
#include "globalsettings_base.h"
#include <KToggleAction>

using namespace MessageViewer;
DefaultGrantleeHeaderStyleInterface::DefaultGrantleeHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent),
      mThemeManager(Q_NULLPTR)
{

}

DefaultGrantleeHeaderStyleInterface::~DefaultGrantleeHeaderStyleInterface()
{

}

void DefaultGrantleeHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    mThemeManager = new GrantleeTheme::ThemeManager(QStringLiteral("mail"),
            QStringLiteral("header.desktop"), ac,
            QStringLiteral("messageviewer/themes/"));
    mThemeManager->setDownloadNewStuffConfigFile(QStringLiteral("messageviewer_header_themes.knsrc"));
    connect(mThemeManager, &GrantleeTheme::ThemeManager::grantleeThemeSelected, this, &DefaultGrantleeHeaderStyleInterface::slotDefaultGrantleeHeaders);
    connect(mThemeManager, &GrantleeTheme::ThemeManager::updateThemes, this, &HeaderStyleInterface::styleUpdated);

    mThemeManager->setActionGroup(actionGroup);
    mThemeManager->setThemeMenu(menu);
    const QString themeName = DefaultGrantleeHeaderStylePluginSettings::self()->themeName();
    mHeaderStylePlugin->headerStyle()->setTheme(mThemeManager->theme(themeName));
    addActionToMenu(menu, actionGroup);
}

void DefaultGrantleeHeaderStyleInterface::activateAction()
{
    KToggleAction *act = mThemeManager->actionForTheme();
    if (act) {
        act->setChecked(true);
    }
}

void DefaultGrantleeHeaderStyleInterface::slotDefaultGrantleeHeaders()
{
    const QString themeName = mThemeManager->configuredThemeName();
    mHeaderStylePlugin->headerStyle()->setTheme(mThemeManager->theme(themeName));
    slotStyleChanged();
}

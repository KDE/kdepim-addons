/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grantleeheaderstyleinterface.h"
#include <GrantleeTheme/GrantleeThemeManager>
#include <KToggleAction>
#include <MessageViewer/HeaderStyle>
#include <MessageViewer/HeaderStylePlugin>

using namespace MessageViewer;
GrantleeHeaderStyleInterface::GrantleeHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
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
                                                    QStringLiteral("header.desktop"),
                                                    ac,
                                                    QStringLiteral("messageviewer/themes/"),
                                                    QStringLiteral("messageviewer_header_themes.knsrc"),
                                                    this);
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

#include "moc_grantleeheaderstyleinterface.cpp"

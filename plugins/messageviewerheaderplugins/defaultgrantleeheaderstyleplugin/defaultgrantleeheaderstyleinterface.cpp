/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "defaultgrantleeheaderstyleinterface.h"
#include "messageviewer/headerstyleplugin.h"
#include "messageviewer/headerstyle.h"
#include <grantleetheme/grantleethememanager.h>
#include "globalsettings_base.h"
#include <KToggleAction>
#include <KActionCollection>
#include <QStandardPaths>

using namespace MessageViewer;
DefaultGrantleeHeaderStyleInterface::DefaultGrantleeHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
    qDebug()<<" DefaultGrantleeHeaderStyleInterface"<<this;
}

DefaultGrantleeHeaderStyleInterface::~DefaultGrantleeHeaderStyleInterface()
{

}

void DefaultGrantleeHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    qDebug()<<" void DefaultGrantleeHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)";
    const QStringList defaultThemePath = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, QStringLiteral("messageviewer/defaultthemes/"), QStandardPaths::LocateDirectory);
    if (!defaultThemePath.isEmpty()) {
        const QString themeName = DefaultGrantleeHeaderStylePluginSettings::self()->themeName();
        mDefaultTheme = GrantleeTheme::ThemeManager::loadTheme(defaultThemePath.at(0) + QLatin1Char('/') + themeName,
                        themeName,
                        QStringLiteral("kmail_default.desktop"));
    }
    mHeaderStylePlugin->headerStyle()->setTheme(mDefaultTheme);
    KToggleAction *act  = new KToggleAction(mDefaultTheme.name(), this);
    ac->addAction(QStringLiteral("default_grantlee_theme"), act);
    connect(act, &KToggleAction::triggered, this, &DefaultGrantleeHeaderStyleInterface::slotDefaultGrantleeHeaders);
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void DefaultGrantleeHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}

void DefaultGrantleeHeaderStyleInterface::slotDefaultGrantleeHeaders()
{
    qDebug()<<" void DefaultGrantleeHeaderStyleInterface::slotDefaultGrantleeHeaders()************";
    mHeaderStylePlugin->headerStyle()->setTheme(mDefaultTheme);
    slotStyleChanged();
}

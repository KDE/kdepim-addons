/*
   Copyright (C) 2015-2018 Montel Laurent <montel@kde.org>

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

#include "enterpriseheaderstyleinterface.h"
#include <KToggleAction>
#include <KLocalizedString>
#include <KActionCollection>
using namespace MessageViewer;
EnterpriseHeaderStyleInterface::EnterpriseHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

EnterpriseHeaderStyleInterface::~EnterpriseHeaderStyleInterface()
{
}

void EnterpriseHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    KToggleAction *act = new KToggleAction(i18nc("View->headers->", "&Enterprise Headers"), this);
    ac->addAction(QStringLiteral("view_headers_enterprise"), act);
    connect(act, &KToggleAction::triggered, this, &EnterpriseHeaderStyleInterface::slotStyleChanged);
    addHelpTextAction(act, i18n("Show the list of headers in Enterprise style"));
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void EnterpriseHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}

/*
   Copyright (C) 2015-2017 Montel Laurent <montel@kde.org>

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

#include "briefheaderstyleinterface.h"
#include <KToggleAction>
#include <KLocalizedString>
#include <KActionCollection>

using namespace MessageViewer;
BriefHeaderStyleInterface::BriefHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

BriefHeaderStyleInterface::~BriefHeaderStyleInterface()
{
}

void BriefHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    KToggleAction *act = new KToggleAction(i18nc("View->headers->", "&Brief Headers"), this);
    ac->addAction(QStringLiteral("view_headers_brief"), act);
    connect(act, &KToggleAction::triggered, this, &BriefHeaderStyleInterface::slotStyleChanged);
    addHelpTextAction(act, i18n("Show brief list of message headers"));
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void BriefHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}

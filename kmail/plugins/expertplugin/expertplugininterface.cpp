/*
   Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

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

#include "expertplugininterface.h"
#include "expertplugin_debug.h"
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

ExpertPluginInterface::ExpertPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

ExpertPluginInterface::~ExpertPluginInterface()
{
}

void ExpertPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->action(QStringLiteral("toggle_mimeparttree"));
    if (action) {
        PimCommon::ActionType type(action, PimCommon::ActionType::Message);
        addActionType(type);
    } else {
        qCWarning(KMAIL_EXPERT_PLUGIN_LOG) << "toggle_mimeparttree is not defined ";
    }
}

void ExpertPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void ExpertPluginInterface::exec()
{
}

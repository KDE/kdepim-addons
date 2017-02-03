/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#include "logactivitiesplugininterface.h"
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <PimCommon/LogActivitiesManager>

LogActivitiesPluginInterface::LogActivitiesPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{

}

LogActivitiesPluginInterface::~LogActivitiesPluginInterface()
{

}

void LogActivitiesPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("&Log Activities..."), this);
    ac->addAction(QStringLiteral("logactivities"), action);
    connect(action, &QAction::triggered, this, &LogActivitiesPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    setActionType(type);
}

void LogActivitiesPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void LogActivitiesPluginInterface::exec()
{
    PimCommon::LogActivitiesManager::self()->showLogActivitiesDialog();
}

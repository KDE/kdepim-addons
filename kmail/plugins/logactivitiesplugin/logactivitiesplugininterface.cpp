/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    addActionType(type);
}

void LogActivitiesPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void LogActivitiesPluginInterface::exec()
{
    PimCommon::LogActivitiesManager::self()->showLogActivitiesDialog();
}

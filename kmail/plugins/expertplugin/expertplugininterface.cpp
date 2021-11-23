/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "expertplugininterface.h"
#include "expertplugin_debug.h"
#include <KActionCollection>
#include <QAction>

ExpertPluginInterface::ExpertPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

ExpertPluginInterface::~ExpertPluginInterface() = default;

void ExpertPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->action(QStringLiteral("toggle_mimeparttree"));
    if (action) {
        const PimCommon::ActionType type(action, PimCommon::ActionType::Message);
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

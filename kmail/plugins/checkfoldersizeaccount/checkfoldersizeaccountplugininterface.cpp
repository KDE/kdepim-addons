/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugininterface.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>

CheckFolderSizeAccountPluginInterface::CheckFolderSizeAccountPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface{parent}
{
}

CheckFolderSizeAccountPluginInterface::~CheckFolderSizeAccountPluginInterface() = default;

void CheckFolderSizeAccountPluginInterface::exec()
{
    // TODO
}

void CheckFolderSizeAccountPluginInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18nc("@action", "&Show Folders Size…"), this);
    ac->addAction(QStringLiteral("showfoldersize"), action);
    connect(action, &QAction::triggered, this, &CheckFolderSizeAccountPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void CheckFolderSizeAccountPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

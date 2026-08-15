/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugininterface.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>

using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountPluginInterface::CheckFolderSizeAccountPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface{parent}
{
}

CheckFolderSizeAccountPluginInterface::~CheckFolderSizeAccountPluginInterface() = default;

void CheckFolderSizeAccountPluginInterface::exec()
{
    if (mCheckFolderSizeDialog) {
        mCheckFolderSizeDialog->raise();
        mCheckFolderSizeDialog->activateWindow();
        return;
    }
    mCheckFolderSizeDialog = new CheckFolderSizeAccountPluginDialog(parentWidget());
    mCheckFolderSizeDialog->show();
}

void CheckFolderSizeAccountPluginInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18nc("@action", "&Show Folders Size…"), this);
    ac->addAction(u"showfoldersize"_s, action);
    connect(action, &QAction::triggered, this, &CheckFolderSizeAccountPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void CheckFolderSizeAccountPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

#include "moc_checkfoldersizeaccountplugininterface.cpp"

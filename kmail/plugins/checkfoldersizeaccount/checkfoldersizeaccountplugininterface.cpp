/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugininterface.h"
using namespace Qt::Literals::StringLiterals;

#include "checkfoldersizeaccountplugindialog.h"

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
    CheckFolderSizeAccountPluginDialog dlg(parentWidget());
    dlg.exec();
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

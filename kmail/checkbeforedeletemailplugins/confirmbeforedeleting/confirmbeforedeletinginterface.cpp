/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "confirmbeforedeletinginterface.h"
#include "confirmbeforedeletingmanager.h"

ConfirmBeforeDeletingInterface::ConfirmBeforeDeletingInterface(QObject *parent)
    : MessageViewer::MessageViewerCheckBeforeDeletingInterface(parent)
{
}

ConfirmBeforeDeletingInterface::~ConfirmBeforeDeletingInterface()
{
}

bool ConfirmBeforeDeletingInterface::exec(Akonadi::Item::List &list)
{
    return ConfirmBeforeDeletingManager::self()->deletingNeedToConfirm(list);
}

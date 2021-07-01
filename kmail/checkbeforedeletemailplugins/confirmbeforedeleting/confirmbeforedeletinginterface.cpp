/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "confirmbeforedeletinginterface.h"
#include "confirmbeforedeletingmanager.h"
#include <KLocalizedString>
#include <KMessageBox>

ConfirmBeforeDeletingInterface::ConfirmBeforeDeletingInterface(QObject *parent)
    : MessageViewer::MessageViewerCheckBeforeDeletingInterface(parent)
{
}

ConfirmBeforeDeletingInterface::~ConfirmBeforeDeletingInterface()
{
}

Akonadi::Item::List ConfirmBeforeDeletingInterface::exec(const Akonadi::Item::List &list)
{
    Akonadi::Item::List lst;
    for (const auto &item : list) {
        if (ConfirmBeforeDeletingManager::self()->deletingNeedToConfirm(item)) {
            // Use subject ?
            if (KMessageBox::questionYesNo(parentWidget(), i18n("Do you want to delete this email?"), i18n("Confirm Delete Mail")) == KMessageBox::No) {
                lst << item;
            }
        } else {
            lst << item;
        }
    }
    return lst;
}

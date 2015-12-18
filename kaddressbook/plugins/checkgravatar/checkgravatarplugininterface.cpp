/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "checkgravatarplugininterface.h"

#include <KMessageBox>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QDebug>

CheckGravatarPluginInterface::CheckGravatarPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{

}

CheckGravatarPluginInterface::~CheckGravatarPluginInterface()
{

}

void CheckGravatarPluginInterface::createAction(KActionCollection *ac)
{
    /*
    QAction *action = ac->addAction(QStringLiteral("send_mail"));
    action->setText(i18n("Send an email..."));
    action->setIcon(QIcon::fromTheme(QStringLiteral("mail-message-new")));
    connect(action, &QAction::triggered, this, &CheckGravatarPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Action);
    setActionType(type);
    */
}

void CheckGravatarPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void CheckGravatarPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    mListItems = items;
}

PimCommon::GenericPluginInterface::RequireTypes CheckGravatarPluginInterface::requires() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void CheckGravatarPluginInterface::exec()
{
    if (mListItems.isEmpty()) {
        KMessageBox::sorry(parentWidget(), i18n("You have not selected any contacts."));
    } else {
    }
}

bool CheckGravatarPluginInterface::hasPopupMenuSupport() const
{
    return true;
}

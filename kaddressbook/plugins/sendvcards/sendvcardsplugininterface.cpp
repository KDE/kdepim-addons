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

#include "sendvcardsplugininterface.h"

#include <KLocalizedString>
#include <KActionCollection>
#include <KIconLoader>
#include <QAction>
#include <QDebug>

SendVcardsPluginInterface::SendVcardsPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{

}

SendVcardsPluginInterface::~SendVcardsPluginInterface()
{

}

void SendVcardsPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("send_vcards"));
    action->setText(i18n("Send vCards..."));
    action->setIcon(KIconLoader::global()->loadIcon(QStringLiteral("mail-message-new"), KIconLoader::Small));
    connect(action, &QAction::triggered, this, &SendVcardsPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    setActionType(type);
}

void SendVcardsPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void SendVcardsPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    mListItems = items;
}

PimCommon::GenericPluginInterface::RequireTypes SendVcardsPluginInterface::requires() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void SendVcardsPluginInterface::exec()
{
    //TODO
}

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

#include "sendmailplugininterface.h"

#include <KMessageBox>
#include <KLocalizedString>
#include <KActionCollection>
#include <KIconLoader>
#include <QAction>
#include <QDebug>

SendMailPluginInterface::SendMailPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{

}

SendMailPluginInterface::~SendMailPluginInterface()
{

}

void SendMailPluginInterface::createAction(KActionCollection *ac)
{
    /*
    QAction *action = ac->addAction(QStringLiteral("send_vcards"));
    action->setText(i18n("Send vCards..."));
    action->setIcon(KIconLoader::global()->loadIcon(QStringLiteral("mail-message-new"), KIconLoader::Small));
    connect(action, &QAction::triggered, this, &SendMailPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Action);
    setActionType(type);
    */
}

void SendMailPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void SendMailPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    mListItems = items;
}

PimCommon::GenericPluginInterface::RequireTypes SendMailPluginInterface::requires() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void SendMailPluginInterface::exec()
{
    if (!mListItems.isEmpty()) {
    }
}

void SendMailPluginInterface::slotSendMailError(const QString &error)
{
    KMessageBox::error(parentWidget(), error);
}

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

#include "sendvcardsjob.h"
#include "sendvcardsplugininterface.h"

#include <KMessageBox>
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

bool SendVcardsPluginInterface::hasPopupMenuSupport() const
{
    return true;
}

void SendVcardsPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("send_vcards"));
    action->setText(i18n("Send vCards..."));
    action->setIcon(QIcon::fromTheme(QStringLiteral("mail-message-new")));
    connect(action, &QAction::triggered, this, &SendVcardsPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Action);
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
    if (!mListItems.isEmpty()) {
        KABSendVCards::SendVcardsJob *sendVcards = new KABSendVCards::SendVcardsJob(mListItems, this);
        connect(sendVcards, &KABSendVCards::SendVcardsJob::sendVCardsError, this, &SendVcardsPluginInterface::slotSendVcardsError);
        sendVcards->start();
    }
}

void SendVcardsPluginInterface::slotSendVcardsError(const QString &error)
{
    KMessageBox::error(parentWidget(), error);
}

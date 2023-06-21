/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sendvcardsplugininterface.h"
#include "kaddressbook_sendvcardsplugin_debug.h"
#include "sendvcardsjob.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>
#include <QAction>

SendVcardsPluginInterface::SendVcardsPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

SendVcardsPluginInterface::~SendVcardsPluginInterface() = default;

void SendVcardsPluginInterface::updateActions(int numberOfSelectedItems, int numberOfSelectedCollections)
{
    Q_UNUSED(numberOfSelectedCollections)
    if (mAction) {
        mAction->setEnabled(numberOfSelectedItems > 0);
    }
}

void SendVcardsPluginInterface::createAction(KActionCollection *ac)
{
    mAction = ac->addAction(QStringLiteral("send_vcards"));
    mAction->setText(i18n("Send vCards..."));
    mAction->setIcon(QIcon::fromTheme(QStringLiteral("mail-message-new")));
    connect(mAction, &QAction::triggered, this, &SendVcardsPluginInterface::slotActivated);
    const PimCommon::ActionType type(mAction, PimCommon::ActionType::Action);
    addActionType(type);
}

void SendVcardsPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void SendVcardsPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    mListItems = items;
}

PimCommon::GenericPluginInterface::RequireTypes SendVcardsPluginInterface::requiresFeatures() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void SendVcardsPluginInterface::exec()
{
    if (!mListItems.isEmpty()) {
        auto sendVcards = new KABSendVCards::SendVcardsJob(mListItems, this);
        connect(sendVcards, &KABSendVCards::SendVcardsJob::sendVCardsError, this, &SendVcardsPluginInterface::slotSendVcardsError);
        if (!sendVcards->start()) {
            qCDebug(KADDRESSBOOK_SENDVCARDS_LOG) << "Impossible to send vcard";
        }
    }
}

void SendVcardsPluginInterface::slotSendVcardsError(const QString &error)
{
    KMessageBox::error(parentWidget(), error);
}

#include "moc_sendvcardsplugininterface.cpp"

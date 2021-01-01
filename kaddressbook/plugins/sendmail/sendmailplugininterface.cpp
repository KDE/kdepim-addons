/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mailsenderjob.h"
#include "sendmailplugininterface.h"

#include <KMessageBox>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QDesktopServices>

SendMailPluginInterface::SendMailPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
    , mAction(nullptr)
{
}

SendMailPluginInterface::~SendMailPluginInterface()
{
}

void SendMailPluginInterface::createAction(KActionCollection *ac)
{
    mAction = ac->addAction(QStringLiteral("send_mail"));
    mAction->setText(i18n("Send an email..."));
    mAction->setIcon(QIcon::fromTheme(QStringLiteral("mail-message-new")));
    connect(mAction, &QAction::triggered, this, &SendMailPluginInterface::slotActivated);
    PimCommon::ActionType type(mAction, PimCommon::ActionType::Action);
    addActionType(type);
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

void SendMailPluginInterface::updateActions(int numberOfSelectedItems, int numberOfSelectedCollections)
{
    Q_UNUSED(numberOfSelectedCollections)
    if (mAction) {
        mAction->setEnabled(numberOfSelectedItems > 0);
    }
}

void SendMailPluginInterface::exec()
{
    if (mListItems.isEmpty()) {
        KMessageBox::sorry(parentWidget(), i18n("You have not selected any contacts."));
    } else {
        auto *mailSender = new KABMailSender::MailSenderJob(mListItems, this);
        connect(mailSender, &KABMailSender::MailSenderJob::sendMails, this, &SendMailPluginInterface::slotSendMails);
        connect(mailSender, &KABMailSender::MailSenderJob::sendMailsError, this, &SendMailPluginInterface::slotSendMailError);
        mailSender->start();
    }
}

void SendMailPluginInterface::slotSendMailError(const QString &error)
{
    KMessageBox::error(parentWidget(), error);
}

void SendMailPluginInterface::slotSendMails(const QStringList &emails)
{
    if (!emails.isEmpty()) {
        QUrl url;
        url.setScheme(QStringLiteral("mailto"));
        url.setPath(emails.join(QLatin1Char(';')));
        QDesktopServices::openUrl(url);
    }
}

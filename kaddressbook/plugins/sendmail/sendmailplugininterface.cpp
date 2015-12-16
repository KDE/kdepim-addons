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

#include "mailsenderjob.h"
#include "sendmailplugininterface.h"

#include <KMessageBox>
#include <KLocalizedString>
#include <KActionCollection>
#include <KIconLoader>
#include <QAction>
#include <QDebug>
#include <QDesktopServices>

SendMailPluginInterface::SendMailPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{

}

SendMailPluginInterface::~SendMailPluginInterface()
{

}

void SendMailPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("send_mail"));
    action->setText(i18n("Send an email..."));
    action->setIcon(QIcon::fromTheme(QStringLiteral("mail-message-new")));
    connect(action, &QAction::triggered, this, &SendMailPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Action);
    setActionType(type);
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
    if (mListItems.isEmpty()) {
        KMessageBox::sorry(parentWidget(), i18n("You have not selected any contacts."));
    } else {
        KABMailSender::MailSenderJob *mailSender = new KABMailSender::MailSenderJob(mListItems, this);
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
        url.setPath(emails.join(QStringLiteral(";")));
        QDesktopServices::openUrl(url);
    }
}

bool SendMailPluginInterface::hasPopupMenuSupport() const
{
    return true;
}

/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sendmailplugininterface.h"
#include "mailsenderjob.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>
#include <QAction>
#include <QDesktopServices>
using namespace Qt::Literals::StringLiterals;

SendMailPluginInterface::SendMailPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

SendMailPluginInterface::~SendMailPluginInterface() = default;

void SendMailPluginInterface::createAction(KActionCollection *ac)
{
    mAction = ac->addAction(u"send_mail"_s);
    mAction->setText(i18n("Send an email…"));
    mAction->setIcon(QIcon::fromTheme(u"mail-message-new"_s));
    connect(mAction, &QAction::triggered, this, &SendMailPluginInterface::slotActivated);
    const PimCommon::ActionType type(mAction, PimCommon::ActionType::Action);
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

PimCommon::GenericPluginInterface::RequireTypes SendMailPluginInterface::requiresFeatures() const
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
        KMessageBox::error(parentWidget(), i18n("You have not selected any contacts."));
    } else {
        auto mailSender = new KABMailSender::MailSenderJob(mListItems, this);
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
        url.setScheme(u"mailto"_s);
        url.setPath(emails.join(u';'));
        QDesktopServices::openUrl(url);
    }
}

#include "moc_sendmailplugininterface.cpp"

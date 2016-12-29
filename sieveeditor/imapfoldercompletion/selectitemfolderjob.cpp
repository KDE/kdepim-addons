/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "selectitemfolderjob.h"
#include "sessionuiproxy.h"
#include "imapfoldercompletionplugin_debug.h"
#include <KIMAP/LoginJob>
#include <KIMAP/Session>
#include <QStandardItemModel>

SelectItemFolderJob::SelectItemFolderJob(QStandardItemModel *model, QObject *parent)
    : QObject(parent),
      mSession(Q_NULLPTR),
      mModel(model)
{

}

SelectItemFolderJob::~SelectItemFolderJob()
{

}

void SelectItemFolderJob::start()
{
    if (mModel && mSieveImapAccount.isValid()) {
        mSession = new KIMAP::Session(mSieveImapAccount.serverName(), mSieveImapAccount.port(), this);
        mSession->setUiProxy(SessionUiProxy::Ptr(new SessionUiProxy));

        KIMAP::LoginJob *login = new KIMAP::LoginJob(mSession);
        login->setUserName(mSieveImapAccount.userName());
        login->setPassword(mSieveImapAccount.password());
        login->setAuthenticationMode(static_cast<KIMAP::LoginJob::AuthenticationMode>(mSieveImapAccount.authenticationType()));
        login->setEncryptionMode(static_cast<KIMAP::LoginJob::EncryptionMode>(mSieveImapAccount.encryptionMode()));
        connect(login, &KIMAP::LoginJob::result, this, &SelectItemFolderJob::slotLoginDone);
        login->start();
    } else {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "SieveImapAccountSettings invalid";
        Q_EMIT finished(false);
        deleteLater();
    }
}

void SelectItemFolderJob::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)
{
#if 0
    qDebug() << " void SelectImapFolderWidget::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)" << account.serverName()
             << " port : " << account.port()
             << " password :" << account.password()
             << "authentication :" << account.authenticationType()
             << "encryption : " << account.encryptionMode();
#endif
    mSieveImapAccount = account;
}

void SelectItemFolderJob::slotLoginDone(KJob *job)
{
    if (!job->error()) {
        slotReloadRequested();
    } else {
        Q_EMIT finished(false);
        deleteLater();
    }
}

void SelectItemFolderJob::slotReloadRequested()
{
    mItemsMap.clear();
    mModel->clear();

    if (!mSession
            || mSession->state() != KIMAP::Session::Authenticated) {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "SubscriptionDialog - got no connection";
        Q_EMIT finished(false);
        deleteLater();
        return;
    }

    KIMAP::ListJob *list = new KIMAP::ListJob(mSession);
    list->setOption(KIMAP::ListJob::IncludeUnsubscribed);
    connect(list, &KIMAP::ListJob::mailBoxesReceived, this, &SelectItemFolderJob::slotMailBoxesReceived);
    connect(list, &KIMAP::ListJob::result, this, &SelectItemFolderJob::slotFullListingDone);
    list->start();
}

void SelectItemFolderJob::slotMailBoxesReceived(const QList<KIMAP::MailBoxDescriptor> &mailBoxes, const QList< QList<QByteArray> > &flags)
{
    const int numberOfMailBoxes(mailBoxes.size());
    for (int i = 0; i < numberOfMailBoxes; i++) {
        KIMAP::MailBoxDescriptor mailBox = mailBoxes[i];

        const QStringList pathParts = mailBox.name.split(mailBox.separator);
        const QString separator = mailBox.separator;
        Q_ASSERT(separator.size() == 1);   // that's what the spec says

        QString parentPath;
        QString currentPath;
        for (int j = 0; j < pathParts.size(); ++j) {
            const QString pathPart = pathParts.at(j);
            currentPath += separator + pathPart;
            const bool isSelectable = !flags[i].contains("\\noselect");
            if (mItemsMap.contains(currentPath)) {
                //nothing
            } else if (!parentPath.isEmpty()) {
                Q_ASSERT(mItemsMap.contains(parentPath));

                QStandardItem *parentItem = mItemsMap[parentPath];

                QStandardItem *item = new QStandardItem(pathPart);
                Qt::ItemFlags flags = Qt::ItemIsEnabled;
                if (isSelectable) {
                    flags |= Qt::ItemIsSelectable;
                }
                item->setFlags(flags);
                item->setData(currentPath.mid(1), PathRole);
                parentItem->appendRow(item);
                mItemsMap[currentPath] = item;

            } else {
                QStandardItem *item = new QStandardItem(pathPart);
                Qt::ItemFlags flags = Qt::ItemIsEnabled;
                if (isSelectable) {
                    flags |= Qt::ItemIsSelectable;
                }
                item->setFlags(flags);
                item->setData(currentPath.mid(1), PathRole);
                mModel->appendRow(item);
                mItemsMap[currentPath] = item;
            }

            parentPath = currentPath;
        }
    }
}

void SelectItemFolderJob::slotFullListingDone(KJob *job)
{
    if (job->error()) {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Error during full listing : " << job->errorString();
        Q_EMIT finished(false);
    }
    Q_EMIT finished(true);
    deleteLater();
}

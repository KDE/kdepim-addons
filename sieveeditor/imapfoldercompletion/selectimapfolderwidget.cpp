/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>
   based on subscriptiondialog from kdepim-runtime

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

#include "selectimapfolderwidget.h"
#include "sessionuiproxy.h"
#include "imapfoldercompletionplugin_debug.h"
#include <QHBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>

#include <KIMAP/Session>
#include <KIMAP/LoginJob>
#include <KSieveUi/SieveAccount>

SelectImapFolderWidget::SelectImapFolderWidget(QWidget *parent)
    : QWidget(parent),
      mSession(Q_NULLPTR)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);
    mTreeView = new QTreeView(this);
    mTreeView->setObjectName(QStringLiteral("treeview"));
    mainLayout->addWidget(mTreeView);

}

SelectImapFolderWidget::~SelectImapFolderWidget()
{

}

void SelectImapFolderWidget::setAccount(const KSieveUi::SieveAccount &account)
{
    mSession = new KIMAP::Session(account.serverName(), account.port(), this);
    mSession->setUiProxy(SessionUiProxy::Ptr(new SessionUiProxy));

    KIMAP::LoginJob *login = new KIMAP::LoginJob(mSession);
    login->setUserName(account.userName());
    login->setPassword(account.password());
#if 0
    login->setEncryptionMode(account.encryptionMode());
    login->setAuthenticationMode(account.authenticationMode());
#endif

    connect(login, &KIMAP::LoginJob::result, this, &SelectImapFolderWidget::onLoginDone);
    login->start();
}

void SelectImapFolderWidget::onLoginDone(KJob *job)
{
    if (!job->error()) {
        onReloadRequested();
    }
}

void SelectImapFolderWidget::onReloadRequested()
{
#if 0
    m_itemsMap.clear();
#endif
    mModel->clear();

    // we need a connection
    if (!mSession
            || mSession->state() != KIMAP::Session::Authenticated) {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "SubscriptionDialog - got no connection";
        Q_EMIT enableOkButton(true);
        return;
    }

    KIMAP::ListJob *list = new KIMAP::ListJob(mSession);
    list->setIncludeUnsubscribed(true);
    connect(list, &KIMAP::ListJob::mailBoxesReceived, this, &SelectImapFolderWidget::onMailBoxesReceived);
    connect(list, &KIMAP::ListJob::result, this, &SelectImapFolderWidget::onFullListingDone);
    list->start();
}

void SelectImapFolderWidget::onMailBoxesReceived(const QList<KIMAP::MailBoxDescriptor> &mailBoxes,
        const QList< QList<QByteArray> > &flags)
{
#if 0
    const int numberOfMailBoxes(mailBoxes.size());
    for (int i = 0; i < numberOfMailBoxes; i++) {
        KIMAP::MailBoxDescriptor mailBox = mailBoxes[i];

        const QStringList pathParts = mailBox.name.split(mailBox.separator);
        const QString separator = mailBox.separator;
        Q_ASSERT(separator.size() == 1);   // that's what the spec says

        QString parentPath;
        QString currentPath;
        const int numberOfPath(pathParts.size());
        for (int j = 0; j < pathParts.size(); ++j) {
            const bool isDummy = (j != (numberOfPath - 1));
            const bool isCheckable = !isDummy && !flags[i].contains("\\noselect");

            const QString pathPart = pathParts.at(j);
            currentPath += separator + pathPart;

            if (m_itemsMap.contains(currentPath)) {
                if (!isDummy) {
                    QStandardItem *item = m_itemsMap[currentPath];
                    item->setCheckable(isCheckable);
                }

            } else if (!parentPath.isEmpty()) {
                Q_ASSERT(m_itemsMap.contains(parentPath));

                QStandardItem *parentItem = m_itemsMap[parentPath];

                QStandardItem *item = new QStandardItem(pathPart);
                item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                item->setCheckable(isCheckable);
                item->setData(currentPath.mid(1), PathRole);
                parentItem->appendRow(item);
                m_itemsMap[currentPath] = item;

            } else {
                QStandardItem *item = new QStandardItem(pathPart);
                item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                item->setCheckable(isCheckable);
                item->setData(currentPath.mid(1), PathRole);
                mModel->appendRow(item);
                m_itemsMap[currentPath] = item;
            }

            parentPath = currentPath;
        }
    }
#endif
}

void SelectImapFolderWidget::onFullListingDone(KJob *job)
{
    if (job->error()) {
        //TODO show error
    }
    Q_EMIT enableOkButton(true);
}

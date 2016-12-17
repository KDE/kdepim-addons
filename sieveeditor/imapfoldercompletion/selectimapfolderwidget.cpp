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
#include <QHeaderView>

#include <KIMAP/Session>
#include <KIMAP/LoginJob>
#include <KSieveUi/SieveImapAccountSettings>
#include <QLineEdit>

SearchFilterProxyModel::SearchFilterProxyModel(QObject *parent)
    : KRecursiveFilterProxyModel(parent)
{

}

void SearchFilterProxyModel::setSearchPattern(const QString &pattern)
{
    if (mPattern != pattern) {
        mPattern = pattern;
        invalidate();
    }
}

bool SearchFilterProxyModel::acceptRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    if (!mPattern.isEmpty()) {
        const QString text = sourceIndex.data(Qt::DisplayRole).toString();
        return text.contains(mPattern, Qt::CaseInsensitive);
    } else {
        return true;
    }
}


SelectImapFolderWidget::SelectImapFolderWidget(QWidget *parent)
    : QWidget(parent),
      mSession(Q_NULLPTR),
      mModel(new QStandardItemModel(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mSearchLineEdit = new QLineEdit(this);
    mSearchLineEdit->setObjectName(QStringLiteral("searchline"));
    mSearchLineEdit->setClearButtonEnabled(true);
    mainLayout->addWidget(mSearchLineEdit);

    mTreeView = new QTreeView(this);
    mTreeView->setObjectName(QStringLiteral("treeview"));
    mTreeView->header()->hide();

    mFilter = new SearchFilterProxyModel(this);
    mFilter->setSourceModel(mModel);

    mTreeView->setModel(mFilter);
    connect(mTreeView, &QTreeView::doubleClicked, this, &SelectImapFolderWidget::slotDoubleClicked);
    mainLayout->addWidget(mTreeView);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &SelectImapFolderWidget::slotSearchPattern);
}

SelectImapFolderWidget::~SelectImapFolderWidget()
{

}

void SelectImapFolderWidget::slotSearchPattern(const QString &pattern)
{
    mTreeView->expandAll();
    mFilter->setSearchPattern(pattern);
}


void SelectImapFolderWidget::slotDoubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        Q_EMIT folderSelected();
    }
}

void SelectImapFolderWidget::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)
{
#if 0
    qDebug() << " void SelectImapFolderWidget::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)" << account.serverName()
             << " port : " << account.port()
             << " password :" << account.password()
             << "authentication :" << account.authenticationType()
             << "encryption : " << account.encryptionMode();
#endif
    if (account.isValid()) {
        mSession = new KIMAP::Session(account.serverName(), account.port(), this);
        mSession->setUiProxy(SessionUiProxy::Ptr(new SessionUiProxy));

        KIMAP::LoginJob *login = new KIMAP::LoginJob(mSession);
        login->setUserName(account.userName());
        login->setPassword(account.password());
        login->setAuthenticationMode(static_cast<KIMAP::LoginJob::AuthenticationMode>(account.authenticationType()));
        login->setEncryptionMode(static_cast<KIMAP::LoginJob::EncryptionMode>(account.encryptionMode()));
        connect(login, &KIMAP::LoginJob::result, this, &SelectImapFolderWidget::slotLoginDone);
        login->start();
    }
}

QString SelectImapFolderWidget::selectedFolderName() const
{
    QString currentPath;
    const QModelIndex index = mTreeView->currentIndex();
    if (index.isValid()) {
        currentPath = index.data(PathRole).toString();
    }
    return currentPath;
}

void SelectImapFolderWidget::slotLoginDone(KJob *job)
{
    if (!job->error()) {
        slotReloadRequested();
    }
}

void SelectImapFolderWidget::slotReloadRequested()
{
    mItemsMap.clear();
    mModel->clear();

    if (!mSession
            || mSession->state() != KIMAP::Session::Authenticated) {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "SubscriptionDialog - got no connection";
        Q_EMIT enableOkButton(true);
        return;
    }

    KIMAP::ListJob *list = new KIMAP::ListJob(mSession);
    list->setIncludeUnsubscribed(true);
    connect(list, &KIMAP::ListJob::mailBoxesReceived, this, &SelectImapFolderWidget::slotMailBoxesReceived);
    connect(list, &KIMAP::ListJob::result, this, &SelectImapFolderWidget::slotFullListingDone);
    list->start();
}

void SelectImapFolderWidget::slotMailBoxesReceived(const QList<KIMAP::MailBoxDescriptor> &mailBoxes, const QList< QList<QByteArray> > &flags)
{
    Q_UNUSED(flags);
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
            if (mItemsMap.contains(currentPath)) {
                //nothing
            } else if (!parentPath.isEmpty()) {
                Q_ASSERT(mItemsMap.contains(parentPath));

                QStandardItem *parentItem = mItemsMap[parentPath];

                QStandardItem *item = new QStandardItem(pathPart);
                item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                item->setData(currentPath.mid(1), PathRole);
                parentItem->appendRow(item);
                mItemsMap[currentPath] = item;

            } else {
                QStandardItem *item = new QStandardItem(pathPart);
                item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                item->setData(currentPath.mid(1), PathRole);
                mModel->appendRow(item);
                mItemsMap[currentPath] = item;
            }

            parentPath = currentPath;
        }
    }
}

void SelectImapFolderWidget::slotFullListingDone(KJob *job)
{
    if (job->error()) {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Error during full listing : " << job->errorString();
    }
    Q_EMIT enableOkButton(true);
}

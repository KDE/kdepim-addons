/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimaploadfoldersjob.h"
#include "imapfoldercompletionplugin_debug.h"
#include "sessionuiproxy.h"
#include <KIMAP/LoginJob>
#include <KIMAP/Session>
#include <KLocalizedString>
#include <KMessageBox>
#include <QStandardItemModel>

SelectImapLoadFoldersJob::SelectImapLoadFoldersJob(QStandardItemModel *model, QObject *parent)
    : QObject(parent)
    , mModel(model)
{
}

SelectImapLoadFoldersJob::~SelectImapLoadFoldersJob() = default;

void SelectImapLoadFoldersJob::start()
{
    if (mModel && mSieveImapAccount.isValid()) {
        mSession = new KIMAP::Session(mSieveImapAccount.serverName(), mSieveImapAccount.port(), this);
        mSession->setUiProxy(SessionUiProxy::Ptr(new SessionUiProxy));

        auto login = new KIMAP::LoginJob(mSession);
        login->setUserName(mSieveImapAccount.userName());
        login->setPassword(mSieveImapAccount.password());
        login->setAuthenticationMode(static_cast<KIMAP::LoginJob::AuthenticationMode>(mSieveImapAccount.authenticationType()));
        login->setEncryptionMode(static_cast<KIMAP::LoginJob::EncryptionMode>(mSieveImapAccount.encryptionMode()));
        connect(login, &KIMAP::LoginJob::result, this, &SelectImapLoadFoldersJob::slotLoginDone);
        login->start();
    } else {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "SieveImapAccountSettings invalid";
        Q_EMIT finished(false, mModel);
        deleteLater();
    }
}

void SelectImapLoadFoldersJob::setSieveImapAccountSettings(const KSieveCore::SieveImapAccountSettings &account)
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

void SelectImapLoadFoldersJob::slotLoginDone(KJob *job)
{
    if (!job->error()) {
        slotReloadRequested();
    } else {
        Q_EMIT finished(false, mModel);
        deleteLater();
    }
}

void SelectImapLoadFoldersJob::slotReloadRequested()
{
    mItemsMap.clear();
    mModel->clear();

    if (!mSession || mSession->state() != KIMAP::Session::Authenticated) {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "SelectImapLoadFoldersJob - got no connection";
        Q_EMIT finished(false, mModel);
        deleteLater();
        return;
    }

    auto list = new KIMAP::ListJob(mSession);
    list->setOption(KIMAP::ListJob::IncludeUnsubscribed);
    connect(list, &KIMAP::ListJob::mailBoxesReceived, this, &SelectImapLoadFoldersJob::slotMailBoxesReceived);
    connect(list, &KIMAP::ListJob::result, this, &SelectImapLoadFoldersJob::slotFullListingDone);
    list->start();
}

void SelectImapLoadFoldersJob::slotMailBoxesReceived(const QList<KIMAP::MailBoxDescriptor> &mailBoxes, const QList<QList<QByteArray>> &flags)
{
    const int numberOfMailBoxes(mailBoxes.size());
    for (int i = 0; i < numberOfMailBoxes; i++) {
        KIMAP::MailBoxDescriptor mailBox = mailBoxes[i];

        const QList<QStringView> pathParts = QStringView(mailBox.name).split(mailBox.separator);
        const QString separator = mailBox.separator;
        Q_ASSERT(separator.size() == 1); // that's what the spec says

        QString parentPath;
        QString currentPath;
        for (int j = 0; j < pathParts.size(); ++j) {
            const QStringView pathPart = pathParts.at(j);
            currentPath += separator + pathPart;
            const bool isSelectable = !flags[i].contains("\\noselect");
            if (mItemsMap.contains(currentPath)) {
                // nothing
            } else if (!parentPath.isEmpty()) {
                Q_ASSERT(mItemsMap.contains(parentPath));

                QStandardItem *parentItem = mItemsMap[parentPath];

                auto item = new QStandardItem(pathPart.toString());
                Qt::ItemFlags itemflags = Qt::ItemIsEnabled;
                if (isSelectable) {
                    itemflags |= Qt::ItemIsSelectable;
                }
                item->setFlags(itemflags);
                item->setData(currentPath.mid(1), PathRole);
                parentItem->appendRow(item);
                mItemsMap[currentPath] = item;
            } else {
                auto item = new QStandardItem(pathPart.toString());
                Qt::ItemFlags itemflags = Qt::ItemIsEnabled;
                if (isSelectable) {
                    itemflags |= Qt::ItemIsSelectable;
                }
                item->setFlags(itemflags);
                item->setData(currentPath.mid(1), PathRole);
                mModel->appendRow(item);
                mItemsMap[currentPath] = item;
            }

            parentPath = currentPath;
        }
    }
}

void SelectImapLoadFoldersJob::slotFullListingDone(KJob *job)
{
    if (job->error()) {
        KMessageBox::error(nullptr, i18n("Error during loading folders: %1", job->errorString()), i18nc("@title:window", "Load Folders"));
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Error during full listing : " << job->errorString();
        Q_EMIT finished(false, mModel);
    } else {
        Q_EMIT finished(true, mModel);
    }
    deleteLater();
}

#include "moc_selectimaploadfoldersjob.cpp"

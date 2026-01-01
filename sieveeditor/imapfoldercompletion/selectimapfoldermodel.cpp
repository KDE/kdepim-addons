/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfoldermodel.h"
#include "imapfoldercompletionplugin_debug.h"
#include "selectimapcreatefolderjob.h"
#include "selectimaploadfoldersjob.h"
#include <QStandardItemModel>

SelectImapFolderModel::SelectImapFolderModel(QObject *parent)
    : QObject(parent)
{
}

SelectImapFolderModel::~SelectImapFolderModel() = default;

SelectImapFolderModel *SelectImapFolderModel::self()
{
    static SelectImapFolderModel s_self;
    return &s_self;
}

void SelectImapFolderModel::createNewFolder(const KSieveCore::SieveImapAccountSettings &account, const QString &folderName)
{
    // qCDebug(IMAPFOLDERCOMPLETIONPLUGIN_LOG)  << " folderName " << folderName;
    auto job = new SelectImapCreateFolderJob(this);
    job->setSieveImapAccountSettings(account);
    job->setNewFolderName(folderName);
    connect(job, &SelectImapCreateFolderJob::finished, this, &SelectImapFolderModel::slotCreateFolderDone);
    job->start();
}

void SelectImapFolderModel::slotCreateFolderDone(const KSieveCore::SieveImapAccountSettings &account, bool success)
{
    if (success) {
        reloadFolderModel(account);
    } else {
        qCDebug(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Unable to create folder";
    }
}

void SelectImapFolderModel::fillModel(const KSieveCore::SieveImapAccountSettings &account, QStandardItemModel *model)
{
    auto job = new SelectImapLoadFoldersJob(model, this);
    job->setSieveImapAccountSettings(account);
    connect(job, &SelectImapLoadFoldersJob::finished, this, &SelectImapFolderModel::slotLoaded);
    job->start();
}

void SelectImapFolderModel::slotLoaded(bool success, QStandardItemModel *model)
{
    Q_EMIT modelLoaded(model, success);
    if (!success) {
        qCDebug(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Unable to load list of folder";
    }
}

void SelectImapFolderModel::reloadFolderModel(const KSieveCore::SieveImapAccountSettings &account)
{
    if (account.isValid()) {
        const QString identifier = account.identifier();
        QStandardItemModel *model = mHashFolderModel.value(identifier);
        if (model) {
            fillModel(account, model);
            mHashFolderModel.insert(identifier, model);
        } else {
            qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Not model defined for account : " << identifier;
        }
    } else {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "account is invalid";
    }
}

QStandardItemModel *SelectImapFolderModel::folderModel(const KSieveCore::SieveImapAccountSettings &account, bool &modelIsInitialized)
{
    QStandardItemModel *model = nullptr;
    if (account.isValid()) {
        const QString identifier = account.identifier();
        model = mHashFolderModel.value(identifier);
        if (!model) {
            model = new QStandardItemModel(this);
            fillModel(account, model);
            mHashFolderModel.insert(identifier, model);
            modelIsInitialized = false;
        } else {
            modelIsInitialized = true;
        }
    } else {
        modelIsInitialized = false;
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "account is invalid";
    }
    return model;
}

#include "moc_selectimapfoldermodel.cpp"

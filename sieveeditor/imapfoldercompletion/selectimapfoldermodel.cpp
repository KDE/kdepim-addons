/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "selectimapfoldermodel.h"
#include "imapfoldercompletionplugin_debug.h"
#include "selectimaploadfoldersjob.h"
#include "selectimapcreatefolderjob.h"
#include <QStandardItemModel>

SelectImapFolderModel::SelectImapFolderModel(QObject *parent)
    : QObject(parent)
{
}

SelectImapFolderModel::~SelectImapFolderModel()
{
}

SelectImapFolderModel *SelectImapFolderModel::self()
{
    static SelectImapFolderModel s_self;
    return &s_self;
}

void SelectImapFolderModel::createNewFolder(const KSieveUi::SieveImapAccountSettings &account, const QString &folderName)
{
    //qCDebug(IMAPFOLDERCOMPLETIONPLUGIN_LOG)  << " folderName " << folderName;
    SelectImapCreateFolderJob *job = new SelectImapCreateFolderJob(this);
    job->setSieveImapAccountSettings(account);
    job->setNewFolderName(folderName);
    connect(job, &SelectImapCreateFolderJob::finished, this, &SelectImapFolderModel::slotCreateFolderDone);
    job->start();
}

void SelectImapFolderModel::slotCreateFolderDone(const KSieveUi::SieveImapAccountSettings &account, bool success)
{
    if (success) {
        reloadFolderModel(account);
    } else {
        qCDebug(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Unable to create folder";
    }
}

void SelectImapFolderModel::fillModel(const KSieveUi::SieveImapAccountSettings &account, QStandardItemModel *model)
{
    SelectImapLoadFoldersJob *job = new SelectImapLoadFoldersJob(model, this);
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

void SelectImapFolderModel::reloadFolderModel(const KSieveUi::SieveImapAccountSettings &account)
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

QStandardItemModel *SelectImapFolderModel::folderModel(const KSieveUi::SieveImapAccountSettings &account, bool &modelIsInitialized)
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

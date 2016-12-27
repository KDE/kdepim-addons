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

#include "selectimapfoldermodel.h"
#include "selectitemfolderjob.h"
#include <QStandardItemModel>

Q_GLOBAL_STATIC(SelectImapFolderModel, s_selectImapFolderModel)

SelectImapFolderModel::SelectImapFolderModel(QObject *parent)
    : QObject(parent)
{
}

SelectImapFolderModel::~SelectImapFolderModel()
{
}

SelectImapFolderModel *SelectImapFolderModel::self()
{
    return s_selectImapFolderModel;
}

QStandardItemModel *SelectImapFolderModel::folderModel(const KSieveUi::SieveImapAccountSettings &account)
{
    const QString identifier = account.identifier();
    QStandardItemModel *model = mHashFolderModel.value(identifier);
    if (!model) {
        model = new QStandardItemModel(this);
        if (account.isValid()) {
            SelectItemFolderJob *job = new SelectItemFolderJob(model, this);
            job->setSieveImapAccountSettings(account);
            job->start();
        }
        mHashFolderModel.insert(identifier, model);
    }
    return model;
}

/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimaplineeditcompletermodel.h"
#include "selectimapfoldermodel.h"

#include <KDescendantsProxyModel>
#include <QStandardItemModel>

SelectImapLineEditCompleterModel::SelectImapLineEditCompleterModel(const KSieveUi::SieveImapAccountSettings &account, QObject *parent)
    : QObject(parent)
    , mFlatProxy(new KDescendantsProxyModel(this))
{
    mFlatProxy->setDisplayAncestorData(true);
    mFlatProxy->setAncestorSeparator(QStringLiteral("/"));
    bool modelIsInitalized = false;
    mFlatProxy->setSourceModel(SelectImapFolderModel::self()->folderModel(account, modelIsInitalized));
}

SelectImapLineEditCompleterModel::~SelectImapLineEditCompleterModel()
{
}

QAbstractProxyModel *SelectImapLineEditCompleterModel::completerModel() const
{
    return mFlatProxy;
}

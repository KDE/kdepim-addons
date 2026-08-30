/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimaplineeditcompletermodel.h"
#include "selectimapfoldermodel.h"

#include <KDescendantsProxyModel>
#include <QStandardItemModel>
using namespace Qt::Literals::StringLiterals;

SelectImapLineEditCompleterModel::SelectImapLineEditCompleterModel(const KSieveCore::SieveImapAccountSettings &account, QObject *parent)
    : QObject(parent)
    , mFlatProxy(new KDescendantsProxyModel(this))
{
    mFlatProxy->setDisplayAncestorData(true);
    mFlatProxy->setAncestorSeparator(u"/"_s);
    bool modelIsInitalized = false;
    mFlatProxy->setSourceModel(SelectImapFolderModel::self()->folderModel(account, modelIsInitalized));
}

SelectImapLineEditCompleterModel::~SelectImapLineEditCompleterModel() = default;

QAbstractProxyModel *SelectImapLineEditCompleterModel::completerModel() const
{
    return mFlatProxy;
}

#include "moc_selectimaplineeditcompletermodel.cpp"

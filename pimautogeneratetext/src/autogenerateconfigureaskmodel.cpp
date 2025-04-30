/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigureaskmodel.h"
#include "pimautogeneratetext_debug.h"

AutogenerateConfigureAskModel::AutogenerateConfigureAskModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

AutogenerateConfigureAskModel::~AutogenerateConfigureAskModel() = default;

int AutogenerateConfigureAskModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mAskItems.count();
}

QVariant AutogenerateConfigureAskModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mAskItems.count()) {
        return {};
    }

    const auto &askItem = mAskItems[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case TitleRole:
        return askItem.title();
    case TextRole:
        return askItem.text();
    case Qt::CheckStateRole:
    case EnabledRole:
        return askItem.enabled();
    }
    return {};
}

bool AutogenerateConfigureAskModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid()) {
        qCWarning(PIMAUTOGENERATE_LOG) << "ERROR: invalid index";
        return false;
    }
    const int id = idx.row();
    auto &info = mAskItems[id];
    switch (role) {
    case AskRoles::TitleRole: {
        info.setTitle(value.toString());
        const QModelIndex newIndex = index(idx.row(), AskRoles::TextRole);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
    case Qt::CheckStateRole:
    case AskRoles::EnabledRole:
        info.setEnabled(value.toBool());
        Q_EMIT dataChanged(idx, idx, {AskRoles::EnabledRole});
        return true;
    }
    return QAbstractListModel::setData(idx, value, role);
}

QList<AutogenerateConfigureAskItem> AutogenerateConfigureAskModel::askItems() const
{
    return mAskItems;
}

void AutogenerateConfigureAskModel::setAskItems(const QList<AutogenerateConfigureAskItem> &newAskItems)
{
    beginResetModel();
    mAskItems = newAskItems;
    endResetModel();
}

void AutogenerateConfigureAskModel::addItem(const AutogenerateConfigureAskItem &msg)
{
    beginInsertRows(QModelIndex(), mAskItems.count(), mAskItems.count());
    mAskItems.append(msg);
    endInsertRows();
}

#include "moc_autogenerateconfigureaskmodel.cpp"

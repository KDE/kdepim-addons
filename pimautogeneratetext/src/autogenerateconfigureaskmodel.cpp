/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

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
    return mAskInfos.count();
}

QVariant AutogenerateConfigureAskModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mAskInfos.count()) {
        return {};
    }

    const auto &askItem = mAskInfos[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case TitleRole:
        return askItem.title().isEmpty() ? askItem.text() : askItem.title();
    case TextRole:
        return askItem.text();
    case Qt::CheckStateRole:
    case EnabledRole:
        return askItem.enabled() ? Qt::Checked : Qt::Unchecked;
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
    auto &info = mAskInfos[id];
    switch (role) {
    case AskRoles::TitleRole: {
        info.setTitle(value.toString());
        const QModelIndex newIndex = index(idx.row(), AskRoles::TitleRole);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
    case AskRoles::TextRole: {
        info.setText(value.toString());
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

QList<AutogenerateConfigureAskInfo> AutogenerateConfigureAskModel::askInfos() const
{
    return mAskInfos;
}

void AutogenerateConfigureAskModel::setAskInfos(const QList<AutogenerateConfigureAskInfo> &newAskItems)
{
    beginResetModel();
    mAskInfos = newAskItems;
    endResetModel();
}

void AutogenerateConfigureAskModel::addItem(const AutogenerateConfigureAskInfo &msg)
{
    beginInsertRows(QModelIndex(), mAskInfos.count(), mAskInfos.count());
    mAskInfos.append(msg);
    endInsertRows();
}

void AutogenerateConfigureAskModel::removeItem(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    mAskInfos.removeAt(index);
    endRemoveRows();
}
Qt::ItemFlags AutogenerateConfigureAskModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsUserCheckable | QAbstractListModel::flags(index);
}

#include "moc_autogenerateconfigureaskmodel.cpp"

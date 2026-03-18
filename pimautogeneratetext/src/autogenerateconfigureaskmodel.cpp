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
    case OrderRole:
        return askItem.order();
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

bool AutogenerateConfigureAskModel::moveRows(const QModelIndex &sourceParent,
                                             int sourceRow,
                                             int count,
                                             const QModelIndex &destinationParent,
                                             int destinationChild)
{
    if (!beginMoveRows(sourceParent, sourceRow, sourceRow + count - 1, destinationParent, destinationChild)) {
        return false; // invalid move, e.g. no-op (move row 2 to row 2 or to row 3)
    }

    for (int i = 0; i < count; ++i) {
        mAskInfos.move(sourceRow + i, destinationChild + (sourceRow > destinationChild ? 0 : -1));
    }
    for (int i = 0; i < mAskInfos.count(); ++i) {
        mAskInfos[i].setOrder(i);
    }
    endMoveRows();
    return true;
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
    if (!index.isValid()) {
        return Qt::ItemIsDropEnabled; // allow dropping between items
    }
    return Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled | QAbstractListModel::flags(index);
}

Qt::DropActions AutogenerateConfigureAskModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

Qt::DropActions AutogenerateConfigureAskModel::supportedDragActions() const
{
    return Qt::MoveAction;
}

QStringList AutogenerateConfigureAskModel::mimeTypes() const
{
    return {QString::fromLatin1("application/x-autogenerate-menu")};
}

#include "moc_autogenerateconfigureaskmodel.cpp"

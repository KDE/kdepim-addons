/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamlistsmodel.h"
#include <KLocalizedString>
#include <MessageViewer/ScamDetectionInfo>

ScamListsModel::ScamListsModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

ScamListsModel::~ScamListsModel() = default;

QList<MessageViewer::ScamDetectionInfo> ScamListsModel::info() const
{
    return mInfo;
}

void ScamListsModel::setInfo(const QList<MessageViewer::ScamDetectionInfo> &newInfo)
{
    beginResetModel();
    mInfo = newInfo;
    endResetModel();
}

int ScamListsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mInfo.count();
}

bool ScamListsModel::insertInfo(const MessageViewer::ScamDetectionInfo &info)
{
    if (mInfo.contains(info)) {
        return false;
    }
    const int numberOfElement = mInfo.count();
    beginInsertRows(QModelIndex(), numberOfElement, mInfo.count());
    mInfo.append(info);
    endInsertRows();
    return true;
}

QVariant ScamListsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (static_cast<ScamRole>(section)) {
        case ScamRole::Domain:
            return i18nc("@title:column", "Domain");
        case ScamRole::Check:
            return i18nc("@title:column", "Check");
        }
    }
    return {};
}

QVariant ScamListsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mInfo.count()) {
        return {};
    }
    if (role != Qt::DisplayRole) {
        return {};
    }

    const MessageViewer::ScamDetectionInfo &info = mInfo.at(index.row());
    const int col = index.column();
    switch (static_cast<ScamRole>(col)) {
    case ScamRole::Domain:
        return info.domainOrEmail();
    case ScamRole::Check:
        return {}; // TODO info.scamChecks();
    }
    return {};
}

int ScamListsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    constexpr int val = static_cast<int>(ScamRole::LastColumn) + 1;
    return val;
}

#include "moc_scamlistsmodel.cpp"

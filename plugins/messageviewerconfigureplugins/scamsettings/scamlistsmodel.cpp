/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamlistsmodel.h"

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

#include "moc_scamlistsmodel.cpp"

/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigureaskmodel.h"

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
    // TODO
    return {};
}

bool AutogenerateConfigureAskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // TODO
    return false;
}

#include "moc_autogenerateconfigureaskmodel.cpp"

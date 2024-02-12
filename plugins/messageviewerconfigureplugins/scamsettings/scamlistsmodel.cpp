/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamlistsmodel.h"

ScamListsModel::ScamListsModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

ScamListsModel::~ScamListsModel() = default;

/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QAbstractListModel>

class AdblockFilterListsModel : public QAbstractListModel
{
public:
    explicit AdblockFilterListsModel(QObject *parent = nullptr);
    ~AdblockFilterListsModel() override;
};

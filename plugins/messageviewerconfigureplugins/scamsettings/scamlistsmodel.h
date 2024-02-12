/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QAbstractListModel>

class ScamListsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ScamListsModel(QObject *parent = nullptr);
    ~ScamListsModel() override;
};

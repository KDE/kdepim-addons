/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QSortFilterProxyModel>

class AutogenerateConfigureAskFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskFilterProxyModel(QObject *parent = nullptr);
    ~AutogenerateConfigureAskFilterProxyModel() override;

    [[nodiscard]] bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;
};

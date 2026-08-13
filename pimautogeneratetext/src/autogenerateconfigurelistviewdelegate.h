/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QItemDelegate>

class AutogenerateConfigureListViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureListViewDelegate(QObject *parent = nullptr);
    ~AutogenerateConfigureListViewDelegate() override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

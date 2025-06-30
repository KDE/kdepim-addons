/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QStyledItemDelegate>
class QTreeView;
class CheckFolderSizeAccountPluginDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginDelegate(QTreeView *view, QObject *parent = nullptr);
    ~CheckFolderSizeAccountPluginDelegate() override;

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QTreeView *const mTreeView;
};

/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QTreeView;
namespace Akonadi
{
class EntityTreeModel;
class ChangeRecorder;
}
class QSortFilterProxyModel;
class CheckFolderSizeAccountPluginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginWidget(QWidget *parent = nullptr);
    ~CheckFolderSizeAccountPluginWidget() override;

private:
    void slotCollectionTreeFetched();
    QTreeView *const mFolderView;
    Akonadi::EntityTreeModel *mModel = nullptr;
    Akonadi::ChangeRecorder *const mChangeRecorder;
    QSortFilterProxyModel *const mCollectionFilter;
};

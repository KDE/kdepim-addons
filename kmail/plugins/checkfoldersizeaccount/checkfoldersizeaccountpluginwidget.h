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
class CheckFolderSizeAccountFilterProxyModel;
class CheckFolderSizeAccountPluginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginWidget(QWidget *parent = nullptr);
    ~CheckFolderSizeAccountPluginWidget() override;

private:
    void slotSetCollectionFilter(const QString &filter);
    void slotCollectionTreeFetched();
    QTreeView *const mFolderView;
    Akonadi::EntityTreeModel *mModel = nullptr;
    Akonadi::ChangeRecorder *const mChangeRecorder;
    CheckFolderSizeAccountFilterProxyModel *const mCollectionFilter;
};

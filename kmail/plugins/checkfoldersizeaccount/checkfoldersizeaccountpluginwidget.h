/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
namespace Akonadi
{
class EntityTreeModel;
class ChangeRecorder;
}
class CheckFolderSizeAccountTreeView;
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
    CheckFolderSizeAccountTreeView *const mFolderView;
    Akonadi::EntityTreeModel *mModel = nullptr;
    Akonadi::ChangeRecorder *const mChangeRecorder;
    CheckFolderSizeAccountFilterProxyModel *const mCollectionFilter;
};

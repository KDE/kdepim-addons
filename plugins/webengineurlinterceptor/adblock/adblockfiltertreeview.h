/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "adblockplugin_private_export.h"

#include <KConfigGroup>
#include <QTreeView>

class AdblockFilterListsModel;
class QSortFilterProxyModel;

class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockFilterTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit AdblockFilterTreeView(QWidget *parent = nullptr);
    ~AdblockFilterTreeView() override;

    void setFilterString(const QString &str);

    void saveSettings();
    void loadSettings();

Q_SIGNALS:
    void settingsChanged();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void slotAddAdblock();
    void slotModifyAdblock(const QModelIndex &index);
    void slotDeleteAdblock(const QModelIndex &index);
    bool mSettingsChanged = false;
    AdblockFilterListsModel *const mAdblockFilterListsModel;
    QSortFilterProxyModel *const mSortFilterProxyModel;
};

/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

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

    void saveSettings() const;
    void loadSettings();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void slotAddAdblock();
    void slotModifyAdblock();
    void slotDeleteAdblock();
    AdblockFilterListsModel *const mAdblockFilterListsModel;
    QSortFilterProxyModel *const mSortFilterProxyModel;
};

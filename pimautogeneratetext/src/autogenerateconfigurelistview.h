/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "autogenerateconfigureaskinfo.h"
#include "pimautogeneratetext_private_export.h"
#include <QListView>
class AutogenerateConfigureAskModel;
class QSortFilterProxyModel;
class PIMAUTOGENERATETEXT_TESTS_EXPORT AutogenerateConfigureListView : public QListView
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureListView(QWidget *parent = nullptr);
    ~AutogenerateConfigureListView() override;

    void setFilterText(const QString &str);

    [[nodiscard]] QList<AutogenerateConfigureAskInfo> askInfos() const;
    void setAskInfos(const QList<AutogenerateConfigureAskInfo> &newAskItems);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    PIMAUTOGENERATETEXT_NO_EXPORT void slotCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    AutogenerateConfigureAskModel *const mModel;
    QSortFilterProxyModel *const mSortFilterProxyModel;
};

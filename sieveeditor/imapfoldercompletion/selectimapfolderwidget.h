/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QTreeView>
#include <QWidget>

#include <KSieveUi/SieveImapAccountSettings>

class QStandardItemModel;
class QLineEdit;
class SelectImapFolderTreeView;
class QSortFilterProxyModel;

class SelectImapFolderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectImapFolderWidget(const KSieveUi::SieveImapAccountSettings &account, QWidget *parent = nullptr);
    ~SelectImapFolderWidget() override;

    Q_REQUIRED_RESULT QString selectedFolderName() const;
    void createFolder();

Q_SIGNALS:
    void folderSelected();
    void folderIsSelected(bool selected);

private:
    void slotModelLoaded(QStandardItemModel *model, bool success);
    void slotDoubleClicked(const QModelIndex &index);
    void slotSearchPattern(const QString &pattern);
    void slotCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void slotRefreshImap();

    const KSieveUi::SieveImapAccountSettings mAccount;
    QLineEdit *const mSearchLineEdit;
    SelectImapFolderTreeView *const mTreeView;
    QStandardItemModel *mModel = nullptr;
    QSortFilterProxyModel *mFilter = nullptr;
};

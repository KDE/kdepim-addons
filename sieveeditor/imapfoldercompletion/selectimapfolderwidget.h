/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QTreeView>
#include <QWidget>

#include <KSieveCore/SieveImapAccountSettings>

class QStandardItemModel;
class QLineEdit;
class SelectImapFolderTreeView;
class QSortFilterProxyModel;

class SelectImapFolderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectImapFolderWidget(const KSieveCore::SieveImapAccountSettings &account, QWidget *parent = nullptr);
    ~SelectImapFolderWidget() override;

    [[nodiscard]] QString selectedFolderName() const;
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

    const KSieveCore::SieveImapAccountSettings mAccount;
    QLineEdit *const mSearchLineEdit;
    SelectImapFolderTreeView *const mTreeView;
    QStandardItemModel *mModel = nullptr;
    QSortFilterProxyModel *mFilter = nullptr;
};

/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPFOLDERWIDGET_H
#define SELECTIMAPFOLDERWIDGET_H

#include <QWidget>
#include <QTreeView>

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
    ~SelectImapFolderWidget();

    QString selectedFolderName() const;
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
    QLineEdit *mSearchLineEdit = nullptr;
    SelectImapFolderTreeView *mTreeView = nullptr;
    QStandardItemModel *mModel = nullptr;
    QSortFilterProxyModel *mFilter = nullptr;
};

#endif // SELECTIMAPFOLDERWIDGET_H

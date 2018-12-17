/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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

    KSieveUi::SieveImapAccountSettings mAccount;
    QLineEdit *mSearchLineEdit = nullptr;
    SelectImapFolderTreeView *mTreeView = nullptr;
    QStandardItemModel *mModel = nullptr;
    QSortFilterProxyModel *mFilter = nullptr;
};

#endif // SELECTIMAPFOLDERWIDGET_H

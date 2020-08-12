/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERSETTINGFILTERPROXYMODEL_H
#define FOLDERSETTINGFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class FolderSettingFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FolderSettingFilterProxyModel(QObject *parent = nullptr);
    ~FolderSettingFilterProxyModel();

    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // FOLDERSETTINGFILTERPROXYMODEL_H

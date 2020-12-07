/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERSETTINGFILTERPROXYMODEL_H
#define FOLDERSETTINGFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <AkonadiCore/Collection>

class FolderSettingFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FolderSettingFilterProxyModel(QObject *parent = nullptr);
    ~FolderSettingFilterProxyModel() override;

    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Q_REQUIRED_RESULT Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_REQUIRED_RESULT Akonadi::Collection::List listCollections() const;

private:
    Akonadi::Collection::List mListCollections;
};

#endif // FOLDERSETTINGFILTERPROXYMODEL_H

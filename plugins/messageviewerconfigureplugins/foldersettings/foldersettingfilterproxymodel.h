/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Collection>
#include <QSortFilterProxyModel>

class FolderSettingFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FolderSettingFilterProxyModel(QObject *parent = nullptr);
    ~FolderSettingFilterProxyModel() override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] Akonadi::Collection::List listCollections() const;

private:
    Akonadi::Collection::List mListCollections;
};

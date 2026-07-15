/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "config-kdepim-addons.h"
#if HAVE_SORTFILTERPROXYMODELBASE
#include <TextAddonsWidgets/SortFilterProxyModelBase>
#else
#include <QSortFilterProxyModel>
#endif

class CheckFolderSizeAccountFilterProxyModel :
#if HAVE_SORTFILTERPROXYMODELBASE
    public TextAddonsWidgets::SortFilterProxyModelBase
#else
    public QSortFilterProxyModel
#endif
{
    Q_OBJECT
public:
    enum FolderSize : uint8_t {
        All,
        MoreThan100K,
        MoreThan1M,
        MoreThan10M,
        Unknown,
    };
    Q_ENUM(FolderSize)

    explicit CheckFolderSizeAccountFilterProxyModel(QObject *parent = nullptr);
    ~CheckFolderSizeAccountFilterProxyModel() override;

    [[nodiscard]] FolderSize folderSize() const;
    void setFolderSize(const FolderSize &newFolderSize);

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    FolderSize mFolderSize = FolderSize::Unknown;
};

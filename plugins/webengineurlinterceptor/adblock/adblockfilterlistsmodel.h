/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "adblockfilter.h"
#include <QAbstractListModel>
class AdblockFilterListsModel : public QAbstractListModel
{
public:
    explicit AdblockFilterListsModel(QObject *parent = nullptr);
    ~AdblockFilterListsModel() override;
    Q_REQUIRED_RESULT QList<AdblockFilter> adblockFilter() const;
    void setAdblockFilter(const QList<AdblockFilter> &newAdblockFilter);

private:
    QList<AdblockFilter> mAdblockFilter;
};

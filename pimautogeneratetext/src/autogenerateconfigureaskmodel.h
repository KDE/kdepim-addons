/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "autogenerateconfigureaskitem.h"

#include <QAbstractListModel>

class AutogenerateConfigureAskModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AskRoles : uint16_t {
        TitleRole = Qt::UserRole + 1,
        TextRole,
        EnabledRole,
    };

    explicit AutogenerateConfigureAskModel(QObject *parent = nullptr);
    ~AutogenerateConfigureAskModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    [[nodiscard]] QList<AutogenerateConfigureAskItem> askItems() const;
    void setAskItems(const QList<AutogenerateConfigureAskItem> &newAskItems);

private:
    QList<AutogenerateConfigureAskItem> mAskItems;
};

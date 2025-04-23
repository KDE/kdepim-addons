/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#pragma once

#include <QSet>
#include <QSortFilterProxyModel>
#include <qqmlintegration.h>

namespace Akonadi
{
class EntityTreeModel;
}

class PimCalendarsModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        CollectionIdRole = Qt::UserRole + 1,
        NameRole,
        EnabledRole,
        CheckedRole,
        IconNameRole,
    };

    explicit PimCalendarsModel(QObject *parent = nullptr);
    ~PimCalendarsModel() override;

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

public Q_SLOTS:
    void setChecked(qint64 collectionId, bool checked);
    void saveConfig();

private:
    Akonadi::EntityTreeModel *mEtm = nullptr;
    QSet<qint64> mEnabledCalendars;
};

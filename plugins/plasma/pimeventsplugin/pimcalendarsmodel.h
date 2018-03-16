/*
 * Copyright (C) 2016  Daniel Vrátil <dvratil@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef PIMCALENDARSMODEL_H
#define PIMCALENDARSMODEL_H

#include <QSortFilterProxyModel>
#include <QSet>

namespace Akonadi {
class EntityTreeModel;
}

class PimCalendarsModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    enum Roles {
        DataRole = Qt::UserRole + 1
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

#endif

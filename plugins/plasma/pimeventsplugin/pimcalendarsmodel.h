/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
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

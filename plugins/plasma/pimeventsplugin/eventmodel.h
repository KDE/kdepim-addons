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

#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <Akonadi/Calendar/CalendarBase>
#include <QVector>

namespace Akonadi
{
class Monitor;
}

class EventModel : public Akonadi::CalendarBase
{
    Q_OBJECT
public:

    explicit EventModel(QObject *parent = Q_NULLPTR);
    ~EventModel();

    QVector<Akonadi::Collection> collections() const;

    Akonadi::Collection collection(qint64 id) const;

public Q_SLOTS:
    void addCalendar(const Akonadi::Collection &col);
    void removeCalendar(const Akonadi::Collection &col);

private Q_SLOTS:
    void onItemsReceived(const Akonadi::Item::List &items);

private:
    void createMonitor();
    void populateCollection(const Akonadi::Collection &col);
    void removeCollection(const Akonadi::Collection &col);

    QVector<Akonadi::Collection> mCols;
    Akonadi::Monitor *mMonitor;
    QMap<Akonadi::Collection::Id, KJob *> mFetchJobs;
};

#endif


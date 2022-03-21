/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#pragma once

#include <Akonadi/CalendarBase>
#include <QVector>

namespace Akonadi
{
class Monitor;
}

class EventModel : public Akonadi::CalendarBase
{
    Q_OBJECT
public:
    explicit EventModel(QObject *parent = nullptr);
    ~EventModel() override;

    Q_REQUIRED_RESULT QVector<Akonadi::Collection> collections() const;

    Q_REQUIRED_RESULT Akonadi::Collection collection(qint64 id) const;

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
    Akonadi::Monitor *mMonitor = nullptr;
    QMap<Akonadi::Collection::Id, KJob *> mFetchJobs;
};

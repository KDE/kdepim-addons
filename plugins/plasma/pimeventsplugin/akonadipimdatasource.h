/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#ifndef AKONADIPIMDATASOURCE_H
#define AKONADIPIMDATASOURCE_H

#include "pimdatasource.h"
#include <QObject>
#include <EventViews/Prefs>

class EventModel;

class AkonadiPimDataSource : public QObject, public PimDataSource
{
    Q_OBJECT

public:
    explicit AkonadiPimDataSource(QObject *parent = nullptr);
    ~AkonadiPimDataSource() override;

    qint64 akonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const override;
    KCalendarCore::Calendar *calendar() const override;
    QString calendarColorForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const override;

private Q_SLOTS:
    void onSettingsChanged();

private:
    EventModel *const mCalendar;
    EventViews::PrefsPtr mEventViewsPrefs;
    mutable QHash<qint64, QString> mColorCache;
};

#endif

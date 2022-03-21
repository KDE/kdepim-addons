/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#pragma once

#include "pimdatasource.h"
#include <EventViews/Prefs>
#include <QObject>

class EventModel;

class AkonadiPimDataSource : public QObject, public PimDataSource
{
    Q_OBJECT

public:
    explicit AkonadiPimDataSource(QObject *parent = nullptr);
    ~AkonadiPimDataSource() override;

    Q_REQUIRED_RESULT qint64 akonadiIdForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const override;
    Q_REQUIRED_RESULT KCalendarCore::Calendar *calendar() const override;
    Q_REQUIRED_RESULT QString calendarColorForIncidence(const KCalendarCore::Incidence::Ptr &incidence) const override;

private Q_SLOTS:
    void onSettingsChanged();

private:
    EventModel *const mCalendar;
    EventViews::PrefsPtr mEventViewsPrefs;
    mutable QHash<qint64, QString> mColorCache;
};

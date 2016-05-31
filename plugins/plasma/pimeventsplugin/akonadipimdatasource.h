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

#ifndef AKONADIPIMDATASOURCE_H
#define AKONADIPIMDATASOURCE_H

#include "pimdatasource.h"
#include <QObject>
#include <EventViews/Prefs>

namespace Akonadi
{
class ChangeRecorder;
class ETMCalendar;
}

class AkonadiPimDataSource : public QObject,
    public PimDataSource
{
    Q_OBJECT

public:
    explicit AkonadiPimDataSource(QObject *parent = Q_NULLPTR);
    ~AkonadiPimDataSource();

    qint64 akonadiIdForIncidence(const KCalCore::Incidence::Ptr &incidence) const Q_DECL_OVERRIDE;
    KCalCore::Calendar *calendar() const Q_DECL_OVERRIDE;
    QString calendarColorForIncidence(const KCalCore::Incidence::Ptr &incidence) const Q_DECL_OVERRIDE;

private Q_SLOTS:
    void onSettingsChanged();

private:
    Akonadi::ChangeRecorder *mMonitor;
    Akonadi::ETMCalendar *mCalendar;
    EventViews::PrefsPtr mEventViewsPrefs;
    mutable QHash<qint64, QString> mColorCache;
};

#endif

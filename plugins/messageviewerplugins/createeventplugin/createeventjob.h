/*
   Copyright (C) 2014-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef CREATEEVENTJOB_H
#define CREATEEVENTJOB_H
#include <KJob>
#include <AkonadiCore/Item>
#include <AkonadiCore/Collection>
#include <KCalCore/Event>

#include <QObject>
namespace MessageViewer
{
class CreateEventJob : public KJob
{
    Q_OBJECT
public:
    explicit CreateEventJob(const KCalCore::Event::Ptr &eventPtr, const Akonadi::Collection &collection, const Akonadi::Item &item, QObject *parent = Q_NULLPTR);
    ~CreateEventJob();

    void start() Q_DECL_OVERRIDE;

private:
    void slotFetchDone(KJob *job);
    void slotEventCreated(KJob *job);
    void slotRelationCreated(KJob *job);
    void createEvent();
    Akonadi::Item mItem;
    Akonadi::Collection mCollection;
    KCalCore::Event::Ptr mEventPtr;
};
}

#endif

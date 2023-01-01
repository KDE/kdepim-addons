/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <Akonadi/Collection>
#include <Akonadi/Item>
#include <KCalendarCore/Event>
#include <KJob>

class QObject;
namespace MessageViewer
{
class CreateEventJob : public KJob
{
    Q_OBJECT
public:
    explicit CreateEventJob(const KCalendarCore::Event::Ptr &eventPtr,
                            const Akonadi::Collection &collection,
                            const Akonadi::Item &item,
                            QObject *parent = nullptr);
    ~CreateEventJob() override;

    void start() override;

private:
    void slotFetchDone(KJob *job);
    void slotEventCreated(KJob *job);
    void slotRelationCreated(KJob *job);
    void createEvent();
    Akonadi::Item mItem;
    const Akonadi::Collection mCollection;
    const KCalendarCore::Event::Ptr mEventPtr;
};
}

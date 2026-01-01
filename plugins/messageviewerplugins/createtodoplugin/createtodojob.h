/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <Akonadi/Collection>
#include <Akonadi/Item>
#include <KCalendarCore/Todo>
#include <KJob>

class QObject;
namespace MessageViewer
{
class CreateTodoJob : public KJob
{
    Q_OBJECT
public:
    explicit CreateTodoJob(const KCalendarCore::Todo::Ptr &todoPtr,
                           const Akonadi::Collection &collection,
                           const Akonadi::Item &item,
                           QObject *parent = nullptr);
    ~CreateTodoJob() override;

    void start() override;

private:
    void slotFetchDone(KJob *job);
    void todoCreated(KJob *job);
    void createTodo();
    Akonadi::Item mItem;
    const Akonadi::Collection mCollection;
    KCalendarCore::Todo::Ptr mTodoPtr;
};
}

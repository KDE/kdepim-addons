/*
   SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <AkonadiCore/Collection>
#include <AkonadiCore/Item>
#include <KCalendarCore/Todo>
#include <KJob>

#include <QObject>
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

private Q_SLOTS:
    void slotFetchDone(KJob *job);
    void todoCreated(KJob *job);
    void relationCreated(KJob *job);

private:
    void createTodo();
    Akonadi::Item mItem;
    const Akonadi::Collection mCollection;
    KCalendarCore::Todo::Ptr mTodoPtr;
};
}


/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CREATETODOJOB_H
#define CREATETODOJOB_H
#include <KJob>
#include <AkonadiCore/Item>
#include <AkonadiCore/Collection>
#include <KCalendarCore/Todo>

#include <QObject>
namespace MessageViewer {
class CreateTodoJob : public KJob
{
    Q_OBJECT
public:
    explicit CreateTodoJob(const KCalendarCore::Todo::Ptr &todoPtr, const Akonadi::Collection &collection, const Akonadi::Item &item, QObject *parent = nullptr);
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

#endif // CREATETODOJOB_H

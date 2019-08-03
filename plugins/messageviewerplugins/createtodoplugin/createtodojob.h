/*
   Copyright (C) 2014-2019 Montel Laurent <montel@kde.org>

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
    Akonadi::Collection mCollection;
    KCalendarCore::Todo::Ptr mTodoPtr;
};
}

#endif // CREATETODOJOB_H

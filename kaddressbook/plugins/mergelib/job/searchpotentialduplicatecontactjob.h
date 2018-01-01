/*
    Copyright (c) 2013-2018 Montel Laurent <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef SEARCHPOTENTIALDUPLICATECONTACTJOB_H
#define SEARCHPOTENTIALDUPLICATECONTACTJOB_H

#include <QObject>
#include <AkonadiCore/Item>

namespace KABMergeContacts {
class SearchPotentialDuplicateContactJob : public QObject
{
    Q_OBJECT
public:
    explicit SearchPotentialDuplicateContactJob(const Akonadi::Item::List &list, QObject *parent = nullptr);
    ~SearchPotentialDuplicateContactJob();

    void start();

    QVector<Akonadi::Item::List> potentialDuplicateContacts() const;

Q_SIGNALS:
    void finished(const QVector<Akonadi::Item::List> &);

private:
    Akonadi::Item::List checkList(const Akonadi::Item::List &lstItem);
    bool isDuplicate(const Akonadi::Item &itemA, const Akonadi::Item &itemB);
    Akonadi::Item::List mListItem;
    QVector<Akonadi::Item::List > mListDuplicate;
};
}

#endif // SEARCHPOTENTIALDUPLICATECONTACTJOB_H

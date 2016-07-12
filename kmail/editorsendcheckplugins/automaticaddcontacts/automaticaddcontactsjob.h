/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#ifndef AUTOMATICADDCONTACTSJOB_H
#define AUTOMATICADDCONTACTSJOB_H

#include <QObject>
#include <AkonadiCore/Collection>
class KJob;
class AutomaticAddContactsJob : public QObject
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsJob(QObject *parent = Q_NULLPTR);
    ~AutomaticAddContactsJob();

    void start();

    void setEmails(const QStringList &emails);
    void setCollection(const Akonadi::Collection &collection);

private:
    void fetchCollection();
    void verifyContactExist();
    void addNextContact();
    QStringList mEmails;
    QStringList mProcessedEmails;
    Akonadi::Collection mCollection;
    int mCurrentIndex;
    void slotCollectionsFetched(KJob *job);
};
#endif // AUTOMATICADDCONTACTSJOB_H

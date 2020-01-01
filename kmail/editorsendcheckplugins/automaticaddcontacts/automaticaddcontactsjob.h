/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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
    explicit AutomaticAddContactsJob(QObject *parent = nullptr);
    ~AutomaticAddContactsJob();

    void start();

    void setEmails(const QStringList &list);
    void setCollection(const Akonadi::Collection &collection);

Q_SIGNALS:
    void finished();

private:
    void fetchCollection();
    void verifyContactExist();
    void addNextContact();
    void slotSelectedCollectionFetched(KJob *job);
    void slotFetchAllCollections(KJob *job);
    void slotSearchDone(KJob *job);
    void slotAddContactDone(KJob *job);
    void slotResourceCreationDone(KJob *);
    void deleteLaterAndEmitSignal();

    QStringList mEmails;
    QStringList mProcessedEmails;
    QString mProcessEmail;
    QString mName;
    Akonadi::Collection mCollection;
    int mCurrentIndex = -1;
};
#endif // AUTOMATICADDCONTACTSJOB_H

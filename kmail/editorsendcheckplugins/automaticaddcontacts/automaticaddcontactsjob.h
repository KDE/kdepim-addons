/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOMATICADDCONTACTSJOB_H
#define AUTOMATICADDCONTACTSJOB_H

#include <AkonadiCore/Collection>
#include <QObject>
class KJob;
class AutomaticAddContactsJob : public QObject
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsJob(QObject *parent = nullptr);
    ~AutomaticAddContactsJob() override;

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

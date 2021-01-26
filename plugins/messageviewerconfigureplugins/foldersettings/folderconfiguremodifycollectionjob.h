/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGUREMODIFYCOLLECTIONJOB_H
#define FOLDERCONFIGUREMODIFYCOLLECTIONJOB_H

#include <AkonadiCore/Collection>
#include <QObject>
class KJob;
class FolderConfigureModifyCollectionJob : public QObject
{
    Q_OBJECT
public:
    explicit FolderConfigureModifyCollectionJob(QObject *parent = nullptr);
    ~FolderConfigureModifyCollectionJob() override;

    void setCollection(const Akonadi::Collection &col);

    void start();

private:
    void slotCollectionModified(KJob *job);
    Akonadi::Collection mCollection;
};

#endif // FOLDERCONFIGUREMODIFYCOLLECTIONJOB_H

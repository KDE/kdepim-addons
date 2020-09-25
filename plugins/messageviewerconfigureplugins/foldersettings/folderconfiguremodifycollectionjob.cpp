/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguremodifycollectionjob.h"
#include "libfolderconfiguresettings_debug.h"
#include <AkonadiCore/CollectionModifyJob>

FolderConfigureModifyCollectionJob::FolderConfigureModifyCollectionJob(QObject *parent)
    : QObject(parent)
{

}

FolderConfigureModifyCollectionJob::~FolderConfigureModifyCollectionJob()
{

}

void FolderConfigureModifyCollectionJob::setCollection(const Akonadi::Collection &col)
{
    mCollection = col;
}

void FolderConfigureModifyCollectionJob::start()
{
    Akonadi::CollectionModifyJob *job = new Akonadi::CollectionModifyJob(mCollection, this);
    connect(job, &Akonadi::CollectionModifyJob::result, this, &FolderConfigureModifyCollectionJob::slotCollectionModified);
}

void FolderConfigureModifyCollectionJob::slotCollectionModified(KJob *job)
{
    if (job->error()) {
        qCWarning(LIBFOLDERCONFIGURESETTINGS_PLUGIN_LOG) << " Error when we modified collection";
    }
    deleteLater();
}

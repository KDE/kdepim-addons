/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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


#include "selectimapcreatefolderjob.h"
#include "imapfoldercompletionplugin_debug.h"
#include <KIMAP/CreateJob>

SelectImapCreateFolderJob::SelectImapCreateFolderJob(QObject *parent)
    : QObject(parent)
{

}

SelectImapCreateFolderJob::~SelectImapCreateFolderJob()
{

}

void SelectImapCreateFolderJob::start()
{
    if (mSieveImapAccount.isValid() && !mNewFolderName.isEmpty()) {
#if 0
        KIMAP::CreateJob *job = new KIMAP::CreateJob(session);
        job->setMailBox(mNewFolderName);

        connect(job, &KIMAP::CreateJob::result, this, &SelectImapCreateFolderJob::slotCreateFolderDone);

        job->start();
#else
        deleteLater();	    
#endif	    
        //TODO
    } else {
        Q_EMIT finished(false);
        deleteLater();
    }
}

void SelectImapCreateFolderJob::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)
{
#if 0
    qDebug() << " void SelectImapFolderWidget::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)" << account.serverName()
             << " port : " << account.port()
             << " password :" << account.password()
             << "authentication :" << account.authenticationType()
             << "encryption : " << account.encryptionMode();
#endif
    mSieveImapAccount = account;
}

void SelectImapCreateFolderJob::setNewFolderName(const QString &newFolderName)
{
    mNewFolderName = newFolderName;
}

void SelectImapCreateFolderJob::slotCreateFolderDone(KJob *job)
{
    if (job->error()) {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Failed to create folder on server: " << job->errorString();
    }
    deleteLater();
}

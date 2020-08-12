/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapcreatefolderjob.h"
#include "imapfoldercompletionplugin_debug.h"
#include "sessionuiproxy.h"
#include <KIMAP/CreateJob>
#include <KIMAP/Session>
#include <KIMAP/LoginJob>
#include <KLocalizedString>
#include <KMessageBox>

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
        mSession = new KIMAP::Session(mSieveImapAccount.serverName(), mSieveImapAccount.port(), this);
        mSession->setUiProxy(SessionUiProxy::Ptr(new SessionUiProxy));

        KIMAP::LoginJob *login = new KIMAP::LoginJob(mSession);
        login->setUserName(mSieveImapAccount.userName());
        login->setPassword(mSieveImapAccount.password());
        login->setAuthenticationMode(static_cast<KIMAP::LoginJob::AuthenticationMode>(mSieveImapAccount.authenticationType()));
        login->setEncryptionMode(static_cast<KIMAP::LoginJob::EncryptionMode>(mSieveImapAccount.encryptionMode()));
        connect(login, &KIMAP::LoginJob::result, this, &SelectImapCreateFolderJob::slotLoginDone);
        login->start();
    } else {
        failed();
    }
}

void SelectImapCreateFolderJob::failed()
{
    Q_EMIT finished(mSieveImapAccount, false);
    deleteLater();
}

void SelectImapCreateFolderJob::slotLoginDone(KJob *job)
{
    if (!job->error()) {
        createFolderRequested();
    } else {
        failed();
    }
}

void SelectImapCreateFolderJob::createFolderRequested()
{
    if (!mSession
        || mSession->state() != KIMAP::Session::Authenticated) {
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "SelectImapCreateFolderJob - got no connection";
        failed();
        return;
    }

    KIMAP::CreateJob *job = new KIMAP::CreateJob(mSession);
    job->setMailBox(mNewFolderName);
    connect(job, &KIMAP::CreateJob::result, this, &SelectImapCreateFolderJob::slotCreateFolderDone);
    job->start();
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
        KMessageBox::error(nullptr, i18n("Error during creating folder: %1", job->errorString()), i18n("Create Folder"));
        qCWarning(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Failed to create folder on server: " << job->errorString();
        Q_EMIT finished(mSieveImapAccount, false);
    } else {
        Q_EMIT finished(mSieveImapAccount, true);
    }
    deleteLater();
}

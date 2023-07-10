/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSieveCore/SieveImapAccountSettings>
#include <QObject>
class KJob;
namespace KIMAP
{
class Session;
}
class SelectImapCreateFolderJob : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapCreateFolderJob(QObject *parent = nullptr);
    ~SelectImapCreateFolderJob() override;
    void start();
    void setSieveImapAccountSettings(const KSieveCore::SieveImapAccountSettings &account);

    void setNewFolderName(const QString &newFolderName);

Q_SIGNALS:
    void finished(const KSieveCore::SieveImapAccountSettings &account, bool success);

private:
    void createFolderRequested();
    void slotCreateFolderDone(KJob *job);
    void slotLoginDone(KJob *job);
    void failed();
    KSieveCore::SieveImapAccountSettings mSieveImapAccount;
    QString mNewFolderName;
    KIMAP::Session *mSession = nullptr;
};

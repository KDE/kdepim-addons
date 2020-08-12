/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPCREATEFOLDERJOB_H
#define SELECTIMAPCREATEFOLDERJOB_H

#include <QObject>
#include <KSieveUi/SieveImapAccountSettings>
class KJob;
namespace KIMAP {
class Session;
}
class SelectImapCreateFolderJob : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapCreateFolderJob(QObject *parent = nullptr);
    ~SelectImapCreateFolderJob();
    void start();
    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account);

    void setNewFolderName(const QString &newFolderName);

Q_SIGNALS:
    void finished(const KSieveUi::SieveImapAccountSettings &account, bool success);

private:
    void createFolderRequested();
    void slotCreateFolderDone(KJob *job);
    void slotLoginDone(KJob *job);
    void failed();
    KSieveUi::SieveImapAccountSettings mSieveImapAccount;
    QString mNewFolderName;
    KIMAP::Session *mSession = nullptr;
};

#endif // SELECTIMAPCREATEJOB_H

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
    KIMAP::Session *mSession = nullptr;
    KSieveUi::SieveImapAccountSettings mSieveImapAccount;
    QString mNewFolderName;
};

#endif // SELECTIMAPCREATEJOB_H

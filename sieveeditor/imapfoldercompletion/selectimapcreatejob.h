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

#ifndef SELECTIMAPCREATEJOB_H
#define SELECTIMAPCREATEJOB_H

#include <QObject>
#include <KSieveUi/SieveImapAccountSettings>
class SelectImapCreateJob : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapCreateJob(QObject *parent = nullptr);
    ~SelectImapCreateJob();
    void start();
    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account);

    void setNewFolderName(const QString &newFolderName);

Q_SIGNALS:
    void finished(bool success);

private:
    KSieveUi::SieveImapAccountSettings mSieveImapAccount;
    QString mNewFolderName;
};

#endif // SELECTIMAPCREATEJOB_H

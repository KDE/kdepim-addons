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

#ifndef SELECTIMAPLOADFOLDERSJOB_H
#define SELECTIMAPLOADFOLDERSJOB_H

#include <QObject>
#include <kimap/listjob.h>
#include <KSieveUi/SieveImapAccountSettings>
namespace KIMAP {
class Session;
}

class QStandardItemModel;
class KJob;
class QStandardItem;
class SelectImapLoadFoldersJob : public QObject
{
    Q_OBJECT
public:
    enum Roles {
        PathRole = Qt::UserRole + 1
    };

    explicit SelectImapLoadFoldersJob(QStandardItemModel *model, QObject *parent = nullptr);
    ~SelectImapLoadFoldersJob();

    void start();

    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account);

Q_SIGNALS:
    void finished(bool success, QStandardItemModel *model);

private:
    void slotLoginDone(KJob *job);
    void slotMailBoxesReceived(const QList<KIMAP::MailBoxDescriptor> &mailBoxes, const QList<QList<QByteArray> > &flags);
    void slotReloadRequested();
    void slotFullListingDone(KJob *job);

    KSieveUi::SieveImapAccountSettings mSieveImapAccount;
    QMap<QString, QStandardItem *> mItemsMap;
    KIMAP::Session *mSession = nullptr;
    QStandardItemModel *mModel = nullptr;
};

#endif // SELECTIMAPLOADFOLDERSJOB_H

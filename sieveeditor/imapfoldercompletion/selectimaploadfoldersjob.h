/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    ~SelectImapLoadFoldersJob() override;

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
    QStandardItemModel *const mModel;
};

#endif // SELECTIMAPLOADFOLDERSJOB_H

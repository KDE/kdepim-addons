/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPFOLDERMODEL_H
#define SELECTIMAPFOLDERMODEL_H

#include <QObject>
#include <QHash>
class QStandardItemModel;
namespace KSieveUi {
class SieveImapAccountSettings;
}
class SelectImapFolderModel : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapFolderModel(QObject *parent = nullptr);
    ~SelectImapFolderModel();

    static SelectImapFolderModel *self();

    QStandardItemModel *folderModel(const KSieveUi::SieveImapAccountSettings &account, bool &modelIsInitialized);

    void reloadFolderModel(const KSieveUi::SieveImapAccountSettings &account);

    void createNewFolder(const KSieveUi::SieveImapAccountSettings &account, const QString &folderName);

Q_SIGNALS:
    void modelLoaded(QStandardItemModel *model, bool success);

private:
    void slotLoaded(bool success, QStandardItemModel *model);
    void slotCreateFolderDone(const KSieveUi::SieveImapAccountSettings &account, bool success);
    void fillModel(const KSieveUi::SieveImapAccountSettings &account, QStandardItemModel *model);
    QHash<QString, QStandardItemModel *> mHashFolderModel;
};

#endif // SELECTIMAPFOLDERMODEL_H

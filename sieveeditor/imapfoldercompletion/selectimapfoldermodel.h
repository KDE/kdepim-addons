/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QHash>
#include <QObject>
class QStandardItemModel;
namespace KSieveCore
{
class SieveImapAccountSettings;
}
class SelectImapFolderModel : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapFolderModel(QObject *parent = nullptr);
    ~SelectImapFolderModel() override;

    static SelectImapFolderModel *self();

    QStandardItemModel *folderModel(const KSieveCore::SieveImapAccountSettings &account, bool &modelIsInitialized);

    void reloadFolderModel(const KSieveCore::SieveImapAccountSettings &account);

    void createNewFolder(const KSieveCore::SieveImapAccountSettings &account, const QString &folderName);

Q_SIGNALS:
    void modelLoaded(QStandardItemModel *model, bool success);

private:
    void slotLoaded(bool success, QStandardItemModel *model);
    void slotCreateFolderDone(const KSieveCore::SieveImapAccountSettings &account, bool success);
    void fillModel(const KSieveCore::SieveImapAccountSettings &account, QStandardItemModel *model);
    QHash<QString, QStandardItemModel *> mHashFolderModel;
};

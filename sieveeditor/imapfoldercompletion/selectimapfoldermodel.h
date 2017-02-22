/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#ifndef SELECTIMAPFOLDERMODEL_H
#define SELECTIMAPFOLDERMODEL_H

#include <QObject>
#include <QHash>
class QStandardItemModel;
namespace KSieveUi
{
class SieveImapAccountSettings;
}
class SelectImapFolderModel : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapFolderModel(QObject *parent = nullptr);
    ~SelectImapFolderModel();

    static SelectImapFolderModel *self();

    QStandardItemModel *folderModel(const KSieveUi::SieveImapAccountSettings &account);

    void reloadFolderModel(const KSieveUi::SieveImapAccountSettings &account);

    void createNewFolder(const KSieveUi::SieveImapAccountSettings &account, const QString &folderName);
Q_SIGNALS:
    void reloadFolders();

private Q_SLOTS:
    void slotLoaded(bool success);
    void slotCreateFolderDone(bool success);

private:
    void fillModel(const KSieveUi::SieveImapAccountSettings &account, QStandardItemModel *model);
    QHash<QString, QStandardItemModel *> mHashFolderModel;
};

#endif // SELECTIMAPFOLDERMODEL_H

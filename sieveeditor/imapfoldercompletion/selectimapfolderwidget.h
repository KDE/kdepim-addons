/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#ifndef SELECTIMAPFOLDERWIDGET_H
#define SELECTIMAPFOLDERWIDGET_H

#include <QWidget>

#include <kimap/listjob.h>
namespace KIMAP
{
class Session;
}
namespace KSieveUi
{
class SieveImapAccountSettings;
}
class QTreeView;
class QStandardItemModel;
class QStandardItem;
class KJob;
class SelectImapFolderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectImapFolderWidget(QWidget *parent = Q_NULLPTR);
    ~SelectImapFolderWidget();

    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account);
    QString selectedFolderName() const;
Q_SIGNALS:
    void enableOkButton(bool enabled);

private:
    enum Roles {
        PathRole = Qt::UserRole + 1
    };
    void onLoginDone(KJob *job);
    void onMailBoxesReceived(const QList<KIMAP::MailBoxDescriptor> &mailBoxes, const QList<QList<QByteArray> > &flags);
    void onReloadRequested();
    void onFullListingDone(KJob *job);

    QMap<QString, QStandardItem *> mItemsMap;
    QTreeView *mTreeView;
    KIMAP::Session *mSession;
    QStandardItemModel *mModel;
};

#endif // SELECTIMAPFOLDERWIDGET_H

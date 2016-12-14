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


#ifndef SELECTIMAPFOLDERDIALOG_H
#define SELECTIMAPFOLDERDIALOG_H

#include <QDialog>
namespace KSieveUi {
class SieveAccount;
}
class SelectImapFolderWidget;
class SelectImapFolderDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectImapFolderDialog(QWidget *parent = Q_NULLPTR);
    ~SelectImapFolderDialog();
    void setSieveAccount(const KSieveUi::SieveAccount &account);

    QString selectedFolderName() const;
private:
    void slotEnableOkButton(bool enabled);
    SelectImapFolderWidget *mSelectImapFolderWidget;
    QPushButton *mOkButton;
};

#endif // SELECTIMAPFOLDERDIALOG_H

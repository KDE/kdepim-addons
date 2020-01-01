/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

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

#ifndef SELECTIMAPLINEEDIT_H
#define SELECTIMAPLINEEDIT_H

#include <QLineEdit>
namespace KSieveUi {
class SieveImapAccountSettings;
}

class SelectImapLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SelectImapLineEdit(QWidget *parent = nullptr);
    ~SelectImapLineEdit();

    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account);
private:
    QCompleter *mCompleter = nullptr;
};

#endif // SELECTIMAPLINEEDIT_H

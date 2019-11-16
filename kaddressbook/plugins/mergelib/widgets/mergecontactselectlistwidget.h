/*
   Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

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

#ifndef MERGECONTACTSELECTLISTWIDGET_H
#define MERGECONTACTSELECTLISTWIDGET_H

#include <AkonadiCore/Item>
#include "kaddressbookmergelib_export.h"
#include "job/mergecontacts.h"
#include <QWidget>
#include <QIcon>
class QLabel;
class QListWidget;
namespace KContacts {
class Addressee;
}
namespace KABMergeContacts {
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectListWidget(QWidget *parent = nullptr);
    ~MergeContactSelectListWidget();

    void setContacts(MergeContacts::ConflictInformation conflictType, const KContacts::Addressee::List &lst);
    Q_REQUIRED_RESULT int selectedContact() const;
    MergeContacts::ConflictInformation conflictType() const;
    Q_REQUIRED_RESULT bool verifySelectedInfo() const;
private:
    void fillList(const KContacts::Addressee::List &lst);
    void updateTitle();
    void addItem(const QString &str, const QIcon &icon = QIcon());
    QLabel *mTitle = nullptr;
    QListWidget *mSelectListWidget = nullptr;
    MergeContacts::ConflictInformation mConflictType;
};
}

#endif // MERGECONTACTSELECTLISTWIDGET_H

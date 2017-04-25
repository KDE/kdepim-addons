/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef MERGECONTACTSELECTINFORMATIONWIDGET_H
#define MERGECONTACTSELECTINFORMATIONWIDGET_H

#include <QWidget>
#include "kaddressbookmergelib_export.h"
#include "job/mergecontacts.h"
#include <AkonadiCore/Item>
namespace KABMergeContacts {
class MergeContactSelectListWidget;
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectInformationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationWidget(QWidget *parent = nullptr);
    ~MergeContactSelectInformationWidget();

    void setContacts(KABMergeContacts::MergeContacts::ConflictInformations conflictTypes, const Akonadi::Item::List &listItem);
    void createContact(KContacts::Addressee &addr);

    bool verifySelectedInfo() const;
private:
    void addInformationWidget(MergeContacts::ConflictInformation conflictType);
    KContacts::Addressee::List mAddressList;
    QVector<MergeContactSelectListWidget *> mListMergeSelectInformation;
};
}

#endif // MERGECONTACTSELECTINFORMATIONWIDGET_H

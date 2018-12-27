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

#ifndef MERGECONTACTSELECTINFORMATIONSCROLLAREA_H
#define MERGECONTACTSELECTINFORMATIONSCROLLAREA_H

#include <QWidget>
#include "kaddressbookmergelib_export.h"
#include "job/mergecontacts.h"
class QStackedWidget;
namespace KABMergeContacts {
class MergeContactSelectInformationWidget;
class MergeContactInfoWidget;
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectInformationScrollArea : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationScrollArea(QWidget *parent = nullptr);
    ~MergeContactSelectInformationScrollArea();
    void setContacts(MergeContacts::ConflictInformations conflictTypes, const Akonadi::Item::List &listItem, const Akonadi::Collection &col);
private:
    void slotMergeContacts();
    void slotMergeDone(const Akonadi::Item &item);
    void mergeContact(const KContacts::Addressee &addr);
    Akonadi::Collection mCollection;
    Akonadi::Item::List mListItem;
    MergeContactSelectInformationWidget *mSelectInformationWidget = nullptr;
    QStackedWidget *mStackWidget = nullptr;
    MergeContactInfoWidget *mMergedContactWidget = nullptr;
};
}

#endif // MERGECONTACTSELECTINFORMATIONSCROLLAREA_H

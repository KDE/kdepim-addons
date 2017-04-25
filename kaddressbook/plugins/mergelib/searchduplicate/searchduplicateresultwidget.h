/*
    Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef SEARCHDUPLICATERESULTWIDGET_H
#define SEARCHDUPLICATERESULTWIDGET_H

#include <QWidget>
#include <AkonadiCore/Item>
#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
class QPushButton;
namespace KAddressBookGrantlee {
class GrantleeContactViewer;
}
namespace Akonadi {
class CollectionComboBox;
}
namespace KABMergeContacts {
class ResultDuplicateTreeWidget;
class MergeContactLoseInformationWarning;

struct MergeConflictResult {
    Akonadi::Item::List list;
    MergeContacts::ConflictInformations conflictInformation;
};

class KADDRESSBOOKMERGELIB_EXPORT SearchDuplicateResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchDuplicateResultWidget(QWidget *parent = nullptr);
    ~SearchDuplicateResultWidget();
    void setContacts(const QVector<Akonadi::Item::List> &lstItem);

Q_SIGNALS:
    void contactMerged(const Akonadi::Item &item);
    void mergeDone();
    void customizeMergeContact(const QVector<KABMergeContacts::MergeConflictResult> &, const Akonadi::Collection &col);

private:
    void slotMergeContact();
    void slotMergeDone(const Akonadi::Item &item);
    void slotUpdateMergeButton();

    void slotAutomaticMerging();
    void slotCustomizeMergingContacts();
    void mergeContact();
    QVector<MergeConflictResult> mResultConflictList;
    QVector<Akonadi::Item::List> mListContactToMerge;
    ResultDuplicateTreeWidget *mResult;
    KAddressBookGrantlee::GrantleeContactViewer *mContactViewer;
    QPushButton *mMergeContact;
    Akonadi::CollectionComboBox *mCollectionCombobox;
    MergeContactLoseInformationWarning *mMergeContactWarning;
    int mIndexListContact;
};
}
Q_DECLARE_TYPEINFO(KABMergeContacts::MergeConflictResult, Q_MOVABLE_TYPE);

#endif // SEARCHDUPLICATERESULTWIDGET_H

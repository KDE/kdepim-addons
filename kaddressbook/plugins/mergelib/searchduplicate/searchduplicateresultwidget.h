/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "job/mergecontacts.h"
#include "kaddressbookmergelib_export.h"
#include <Akonadi/Item>
#include <QWidget>
class QPushButton;
class KTreeWidgetSearchLineWidget;
namespace KAddressBookGrantlee
{
class GrantleeContactViewer;
}
namespace Akonadi
{
class CollectionComboBox;
}
namespace KABMergeContacts
{
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
    ~SearchDuplicateResultWidget() override;
    void setContacts(const QList<Akonadi::Item::List> &lstItem);

Q_SIGNALS:
    void contactMerged(const Akonadi::Item &item);
    void mergeDone();
    void customizeMergeContact(const QList<KABMergeContacts::MergeConflictResult> &, const Akonadi::Collection &col);

private:
    void slotMergeContact();
    void slotMergeDone(const Akonadi::Item &item);
    void slotUpdateMergeButton();

    void slotAutomaticMerging();
    void slotCustomizeMergingContacts();
    void mergeContact();
    void slotCustomContextMenuRequested(const QPoint &);
    void slotExpandAll();
    void slotCollapseAll();
    void slotSelectAll();
    void slotDeselectAll();
    QList<MergeConflictResult> mResultConflictList;
    QList<Akonadi::Item::List> mListContactToMerge;
    ResultDuplicateTreeWidget *const mResultTreeWidget;
    KAddressBookGrantlee::GrantleeContactViewer *const mContactViewer;
    QPushButton *mMergeContact = nullptr;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    MergeContactLoseInformationWarning *const mMergeContactWarning;
    KTreeWidgetSearchLineWidget *mSearchInResultLineEdit = nullptr;
    int mIndexListContact = 0;
};
}
Q_DECLARE_TYPEINFO(KABMergeContacts::MergeConflictResult, Q_RELOCATABLE_TYPE);

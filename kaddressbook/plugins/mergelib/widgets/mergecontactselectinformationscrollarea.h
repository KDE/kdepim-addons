/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    ~MergeContactSelectInformationScrollArea() override;
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

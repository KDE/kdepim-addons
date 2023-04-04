/*
    SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Item>
#include <QDialog>

#include "kaddressbookmergelib_export.h"
#include "searchduplicateresultwidget.h"
class QStackedWidget;
namespace KABMergeContacts
{
class SearchDuplicateResultWidget;
class MergeContactShowResultTabWidget;
class MergeContactSelectInformationTabWidget;
class MergeContactErrorLabel;

class KADDRESSBOOKMERGELIB_EXPORT SearchAndMergeContactDuplicateContactDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SearchAndMergeContactDuplicateContactDialog(QWidget *parent = nullptr);
    ~SearchAndMergeContactDuplicateContactDialog() override;

    void searchPotentialDuplicateContacts(const Akonadi::Item::List &list);

private:
    void slotDuplicateFound(const QList<Akonadi::Item::List> &duplicate);
    void slotMergeDone();
    void slotContactMerged(const Akonadi::Item &item);
    void slotCustomizeMergeContacts(const QList<KABMergeContacts::MergeConflictResult> &lst, const Akonadi::Collection &col);
    void readConfig();
    void writeConfig();
    SearchDuplicateResultWidget *const mSearchResult;
    MergeContactShowResultTabWidget *const mMergeContactResult;
    KABMergeContacts::MergeContactErrorLabel *const mNoContactSelected;
    KABMergeContacts::MergeContactErrorLabel *const mNoDuplicateContactFound;
    KABMergeContacts::MergeContactErrorLabel *const mNoEnoughContactSelected;
    KABMergeContacts::MergeContactSelectInformationTabWidget *const mSelectInformation;
    QStackedWidget *const mStackedWidget;
};
}

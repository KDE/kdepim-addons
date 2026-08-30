/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "searchandmergecontactduplicatecontactdialogtest.h"

#include "../searchduplicate/searchandmergecontactduplicatecontactdialog.h"

#include <QStandardPaths>
#include <QTest>

#include <QStackedWidget>
using namespace Qt::Literals::StringLiterals;
using namespace KABMergeContacts;

SearchAndMergeContactDuplicateContactDialogTest::SearchAndMergeContactDuplicateContactDialogTest(QObject *parent)
    : QObject(parent)
{
}

void SearchAndMergeContactDuplicateContactDialogTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
}

void SearchAndMergeContactDuplicateContactDialogTest::shouldHaveDefaultValueOnCreation()
{
    SearchAndMergeContactDuplicateContactDialog dlg;
    dlg.show();
    const auto stackedWidget = dlg.findChild<QStackedWidget *>(u"stackedwidget"_s);
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), u"nocontactselected"_s);

    for (int i = 0; i < stackedWidget->count(); ++i) {
        QWidget *w = stackedWidget->widget(i);
        const QString objName = w->objectName();
        const bool hasGoodNamePage = (objName == "mergecontact"_L1 || objName == "nocontactselected"_L1 || objName == "nocontactduplicatesfound"_L1
                                      || objName == "noenoughcontactselected"_L1 || objName == "mergecontactresult"_L1 || objName == "selectioninformation"_L1);
        QVERIFY(hasGoodNamePage);
    }
}

void SearchAndMergeContactDuplicateContactDialogTest::shouldShowNoEnoughPageWhenSelectOneContact()
{
    SearchAndMergeContactDuplicateContactDialog dlg;
    Akonadi::Item::List lst;
    lst << Akonadi::Item(42);
    dlg.searchPotentialDuplicateContacts(lst);
    dlg.show();
    const auto stackedWidget = dlg.findChild<QStackedWidget *>(u"stackedwidget"_s);
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), u"noenoughcontactselected"_s);
}

void SearchAndMergeContactDuplicateContactDialogTest::shouldShowNoContactWhenListIsEmpty()
{
    SearchAndMergeContactDuplicateContactDialog dlg;
    Akonadi::Item::List lst;
    dlg.searchPotentialDuplicateContacts(lst);
    dlg.show();
    const auto stackedWidget = dlg.findChild<QStackedWidget *>(u"stackedwidget"_s);
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), u"nocontactselected"_s);
}

QTEST_MAIN(SearchAndMergeContactDuplicateContactDialogTest)

#include "moc_searchandmergecontactduplicatecontactdialogtest.cpp"

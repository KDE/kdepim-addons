/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "searchandmergecontactduplicatecontactdialogtest.h"

#include "../searchduplicate/searchandmergecontactduplicatecontactdialog.h"

#include <QStandardPaths>
#include <QTest>

#include <QStackedWidget>
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
    auto stackedWidget = dlg.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("nocontactselected"));

    for (int i = 0; i < stackedWidget->count(); ++i) {
        QWidget *w = stackedWidget->widget(i);
        const QString objName = w->objectName();
        const bool hasGoodNamePage = (objName == QLatin1String("mergecontact") || objName == QLatin1String("nocontactselected")
                                      || objName == QLatin1String("nocontactduplicatesfound") || objName == QLatin1String("noenoughcontactselected")
                                      || objName == QLatin1String("mergecontactresult") || objName == QLatin1String("selectioninformation"));
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
    auto stackedWidget = dlg.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("noenoughcontactselected"));
}

void SearchAndMergeContactDuplicateContactDialogTest::shouldShowNoContactWhenListIsEmpty()
{
    SearchAndMergeContactDuplicateContactDialog dlg;
    Akonadi::Item::List lst;
    dlg.searchPotentialDuplicateContacts(lst);
    dlg.show();
    auto stackedWidget = dlg.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("nocontactselected"));
}

QTEST_MAIN(SearchAndMergeContactDuplicateContactDialogTest)

#include "moc_searchandmergecontactduplicatecontactdialogtest.cpp"

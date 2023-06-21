/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactsdialogtest.h"
#include "manualmerge/mergecontactsdialog.h"

#include <QStackedWidget>
#include <QTest>

#include <QDialogButtonBox>
#include <QStandardPaths>

MergeContactsDialogTest::MergeContactsDialogTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactsDialogTest::~MergeContactsDialogTest() = default;

void MergeContactsDialogTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
}

void MergeContactsDialogTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactsDialog dlg;
    dlg.show();

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    auto stackedWidget = dlg.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("nocontactselected"));

    for (int i = 0; i < stackedWidget->count(); ++i) {
        QWidget *w = stackedWidget->widget(i);
        const QString objName = w->objectName();
        const bool hasGoodNamePage = (objName == QLatin1String("notenoughcontactselected") || objName == QLatin1String("nocontactselected")
                                      || objName == QLatin1String("manualmergeresultwidget") || objName == QLatin1String("selectioninformation")
                                      || objName == QLatin1String("mergecontactinfowidget"));
        QVERIFY(hasGoodNamePage);
    }
}

void MergeContactsDialogTest::shouldSwithStackedWidget()
{
    KABMergeContacts::MergeContactsDialog dlg;
    dlg.show();
    auto stackedWidget = dlg.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    Akonadi::Item::List lst;
    // Empty
    dlg.setContacts(lst);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("nocontactselected"));
    lst << Akonadi::Item(42);
    // 1 element
    dlg.setContacts(lst);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("notenoughcontactselected"));
    lst.clear();
    // 1 element
    lst << Akonadi::Item(42);
    dlg.setContacts(lst);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("notenoughcontactselected"));
    // 2 elements
    lst.clear();
    lst << Akonadi::Item(42) << Akonadi::Item(42);
    dlg.setContacts(lst);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), QStringLiteral("manualmergeresultwidget"));
}

QTEST_MAIN(MergeContactsDialogTest)

#include "moc_mergecontactsdialogtest.cpp"

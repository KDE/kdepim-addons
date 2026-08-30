/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactsdialogtest.h"
#include "manualmerge/mergecontactsdialog.h"

#include <QStackedWidget>
#include <QTest>

#include <QDialogButtonBox>
#include <QStandardPaths>
using namespace Qt::Literals::StringLiterals;

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

    const auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    const auto stackedWidget = dlg.findChild<QStackedWidget *>(u"stackedwidget"_s);
    QVERIFY(stackedWidget);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), u"nocontactselected"_s);

    for (int i = 0; i < stackedWidget->count(); ++i) {
        QWidget *w = stackedWidget->widget(i);
        const QString objName = w->objectName();
        const bool hasGoodNamePage = (objName == QLatin1StringView("notenoughcontactselected") || objName == QLatin1StringView("nocontactselected")
                                      || objName == QLatin1StringView("manualmergeresultwidget") || objName == QLatin1StringView("selectioninformation")
                                      || objName == QLatin1StringView("mergecontactinfowidget"));
        QVERIFY(hasGoodNamePage);
    }
}

void MergeContactsDialogTest::shouldSwithStackedWidget()
{
    KABMergeContacts::MergeContactsDialog dlg;
    dlg.show();
    const auto stackedWidget = dlg.findChild<QStackedWidget *>(u"stackedwidget"_s);
    Akonadi::Item::List lst;
    // Empty
    dlg.setContacts(lst);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), u"nocontactselected"_s);
    lst << Akonadi::Item(42);
    // 1 element
    dlg.setContacts(lst);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), u"notenoughcontactselected"_s);
    lst.clear();
    // 1 element
    lst << Akonadi::Item(42);
    dlg.setContacts(lst);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), u"notenoughcontactselected"_s);
    // 2 elements
    lst.clear();
    lst << Akonadi::Item(42) << Akonadi::Item(42);
    dlg.setContacts(lst);
    QCOMPARE(stackedWidget->currentWidget()->objectName(), u"manualmergeresultwidget"_s);
}

QTEST_MAIN(MergeContactsDialogTest)

#include "moc_mergecontactsdialogtest.cpp"

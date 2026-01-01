/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingcreaterulewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmbeforedeletingcreaterulewidget.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(ConfirmBeforeDeletingCreateRuleWidgetTest)
ConfirmBeforeDeletingCreateRuleWidgetTest::ConfirmBeforeDeletingCreateRuleWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingCreateRuleWidgetTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingCreateRuleWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mPatternLineEdit = w.findChild<QLineEdit *>(u"mPatternLineEdit"_s);
    QVERIFY(mPatternLineEdit);
    QVERIFY(mPatternLineEdit->text().isEmpty());

    auto mRuleTypeComboBox = w.findChild<QComboBox *>(u"mRuleTypeComboBox"_s);
    QVERIFY(mRuleTypeComboBox);
    QVERIFY(mRuleTypeComboBox->count() > 0);

    auto label = w.findChild<QLabel *>(u"typeLabel"_s);
    QVERIFY(!label->text().isEmpty());

    label = w.findChild<QLabel *>(u"containsLabel"_s);
    QVERIFY(!label->text().isEmpty());
}

#include "moc_confirmbeforedeletingcreaterulewidgettest.cpp"

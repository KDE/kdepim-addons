/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingcreateruledialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmbeforedeletingcreateruledialog.h"
#include "confirmbeforedeletingcreaterulewidget.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(ConfirmBeforeDeletingCreateRuleDialogTest)
ConfirmBeforeDeletingCreateRuleDialogTest::ConfirmBeforeDeletingCreateRuleDialogTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingCreateRuleDialogTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingCreateRuleDialog w;
    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto mConfirmBeforeDeletingCreateRuleWidget = w.findChild<ConfirmBeforeDeletingCreateRuleWidget *>(u"mConfirmBeforeDeletingCreateRuleWidget"_s);
    mainLayout->addWidget(mConfirmBeforeDeletingCreateRuleWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
    auto okButton = buttonBox->button(QDialogButtonBox::Ok);
    QVERIFY(!okButton->isEnabled());
}

#include "moc_confirmbeforedeletingcreateruledialogtest.cpp"

/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingdialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmbeforedeletingdialog.h"
#include "confirmbeforedeletingwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(ConfirmBeforeDeletingDialogTest)
ConfirmBeforeDeletingDialogTest::ConfirmBeforeDeletingDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void ConfirmBeforeDeletingDialogTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingDialog d;
    QVERIFY(!d.windowTitle().isEmpty());
    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto mConfirmBeforeDeletingWidget = d.findChild<ConfirmBeforeDeletingWidget *>(u"mConfirmBeforeDeletingWidget"_s);
    QVERIFY(mConfirmBeforeDeletingWidget);

    auto buttonBox = d.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
}

#include "moc_confirmbeforedeletingdialogtest.cpp"

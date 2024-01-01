/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingdialogtest.h"
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
    auto mainLayout = d.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mConfirmBeforeDeletingWidget = d.findChild<ConfirmBeforeDeletingWidget *>(QStringLiteral("mConfirmBeforeDeletingWidget"));
    QVERIFY(mConfirmBeforeDeletingWidget);

    auto buttonBox = d.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
}

#include "moc_confirmbeforedeletingdialogtest.cpp"

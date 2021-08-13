/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxdialogtest.h"
#include "confirmbeforedeletingmessageboxdialog.h"
#include "confirmbeforedeletingmessageboxwidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(ConfirmBeforeDeletingMessageBoxDialogTest)
ConfirmBeforeDeletingMessageBoxDialogTest::ConfirmBeforeDeletingMessageBoxDialogTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingMessageBoxDialogTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingMessageBoxDialog d;

    QVERIFY(!d.windowTitle().isEmpty());
    QVERIFY(!d.useSameResult());

    auto mainLayout = d.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mConfirmBeforeDeletingWidget = d.findChild<ConfirmBeforeDeletingMessageBoxWidget *>(QStringLiteral("mConfirmBeforeDeletingWidget"));
    QVERIFY(mConfirmBeforeDeletingWidget);

    auto buttonBox = d.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), QDialogButtonBox::Yes | QDialogButtonBox::Cancel | QDialogButtonBox::No);
}

/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxdialogtest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mConfirmBeforeDeletingWidget = d.findChild<ConfirmBeforeDeletingMessageBoxWidget *>(u"mConfirmBeforeDeletingWidget"_s);
    QVERIFY(mConfirmBeforeDeletingWidget);

    auto buttonBox = d.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), QDialogButtonBox::Yes | QDialogButtonBox::Cancel | QDialogButtonBox::No);
}

#include "moc_confirmbeforedeletingmessageboxdialogtest.cpp"

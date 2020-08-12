/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressemailentrydialogtest.h"
#include "../confirmaddressemailentrydialog.h"
#include <PimCommon/EmailValidator>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(ConfirmAddressEmailEntryDialogTest)

ConfirmAddressEmailEntryDialogTest::ConfirmAddressEmailEntryDialogTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmAddressEmailEntryDialogTest::shouldHaveDefaultValue()
{
    ConfirmAddressEmailEntryDialog dlg;
    QVBoxLayout *mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    QLabel *label = dlg.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    QLineEdit *mLineEdit = dlg.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());
    QVERIFY(mLineEdit->validator());
    QVERIFY(qobject_cast<const PimCommon::EmailValidator *>(mLineEdit->validator()));

    QDialogButtonBox *buttons = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttons"));
    QVERIFY(buttons);
}

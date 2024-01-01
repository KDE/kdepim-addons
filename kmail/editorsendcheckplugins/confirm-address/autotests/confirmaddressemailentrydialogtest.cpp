/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressemailentrydialogtest.h"
#include "../confirmaddressemailentrydialog.h"
#include <KEmailValidator>
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
    auto mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto label = dlg.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto mLineEdit = dlg.findChild<QLineEdit *>(QStringLiteral("lineedit"));
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());
    QVERIFY(mLineEdit->validator());
    QVERIFY(qobject_cast<const KEmailValidator *>(mLineEdit->validator()));

    auto buttons = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttons"));
    QVERIFY(buttons);
}

#include "moc_confirmaddressemailentrydialogtest.cpp"

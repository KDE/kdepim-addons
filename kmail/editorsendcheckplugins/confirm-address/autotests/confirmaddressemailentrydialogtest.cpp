/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressemailentrydialogtest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = dlg.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto label = dlg.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto mLineEdit = dlg.findChild<QLineEdit *>(u"lineedit"_s);
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());
    QVERIFY(mLineEdit->validator());
    QVERIFY(qobject_cast<const KEmailValidator *>(mLineEdit->validator()));

    auto buttons = dlg.findChild<QDialogButtonBox *>(u"buttons"_s);
    QVERIFY(buttons);
}

#include "moc_confirmaddressemailentrydialogtest.cpp"

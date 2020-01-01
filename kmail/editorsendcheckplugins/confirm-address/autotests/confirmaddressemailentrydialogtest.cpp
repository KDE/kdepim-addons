/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "confirmaddressemailentrydialogtest.h"
#include "../confirmaddressemailentrydialog.h"
#include <EmailValidator>
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
    QVERIFY(qobject_cast<const KPIM::EmailValidator *>(mLineEdit->validator()));

    QDialogButtonBox *buttons = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttons"));
    QVERIFY(buttons);
}

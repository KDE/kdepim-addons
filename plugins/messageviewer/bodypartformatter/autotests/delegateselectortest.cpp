/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "delegateselectortest.h"
#include "../calendar/delegateselector.h"
#include <QTest>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <Libkdepim/AddresseeLineEdit>

DelegateSelectorTest::DelegateSelectorTest(QObject *parent)
    : QObject(parent)
{

}

DelegateSelectorTest::~DelegateSelectorTest()
{

}

void DelegateSelectorTest::shouldHaveDefaultValue()
{
    DelegateSelector w;
    QLabel *label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    KPIM::AddresseeLineEdit *mDelegate = w.findChild<KPIM::AddresseeLineEdit *>(QStringLiteral("delegate"));
    QVERIFY(mDelegate);
    QVERIFY(mDelegate->text().isEmpty());

    QCheckBox *mRsvp = w.findChild<QCheckBox *>(QStringLiteral("informcheckbox"));
    QVERIFY(mRsvp);
    QVERIFY(mRsvp->isChecked());
    QVERIFY(!mRsvp->text().isEmpty());

    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QPushButton *mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    QVERIFY(mOkButton);
    QVERIFY(!mOkButton->isEnabled());
}

void DelegateSelectorTest::shouldChangeOkButtonState()
{
    DelegateSelector w;
    KPIM::AddresseeLineEdit *mDelegate = w.findChild<KPIM::AddresseeLineEdit *>(QStringLiteral("delegate"));
    //mDelegate->setEnableAkonadiSearch(false);
    mDelegate->setEnableBalooSearch(false);

    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QPushButton *mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    QVERIFY(!mOkButton->isEnabled());

    mDelegate->setText(QStringLiteral("foo"));
    QVERIFY(mOkButton->isEnabled());

    mDelegate->clear();
    QVERIFY(!mOkButton->isEnabled());
    mDelegate->setText(QStringLiteral(" "));
    QVERIFY(!mOkButton->isEnabled());
}

void DelegateSelectorTest::shouldReturnCheckBoxState()
{
    DelegateSelector w;
    QCheckBox *mRsvp = w.findChild<QCheckBox *>(QStringLiteral("informcheckbox"));
    QVERIFY(mRsvp->isChecked());
    mRsvp->setChecked(true);
    QVERIFY(w.rsvp());

    mRsvp->setChecked(false);
    QVERIFY(!w.rsvp());
}

QTEST_MAIN(DelegateSelectorTest)

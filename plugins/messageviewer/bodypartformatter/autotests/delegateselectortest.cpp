/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "delegateselectortest.h"
#include "../calendar/delegateselector.h"
#include <QTest>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <PimCommonAkonadi/AddresseeLineEdit>

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

    PimCommon::AddresseeLineEdit *mDelegate = w.findChild<PimCommon::AddresseeLineEdit *>(QStringLiteral("delegate"));
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
    PimCommon::AddresseeLineEdit *mDelegate = w.findChild<PimCommon::AddresseeLineEdit *>(QStringLiteral("delegate"));
    mDelegate->setEnableAkonadiSearch(false);
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

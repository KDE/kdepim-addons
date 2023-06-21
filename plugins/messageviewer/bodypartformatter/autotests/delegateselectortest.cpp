/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "delegateselectortest.h"
#include "../calendar/delegateselector.h"
#include <PimCommonAkonadi/AddresseeLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QTest>

DelegateSelectorTest::DelegateSelectorTest(QObject *parent)
    : QObject(parent)
{
}

DelegateSelectorTest::~DelegateSelectorTest() = default;

void DelegateSelectorTest::shouldHaveDefaultValue()
{
    DelegateSelector w;
    auto label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto mDelegate = w.findChild<PimCommon::AddresseeLineEdit *>(QStringLiteral("delegate"));
    QVERIFY(mDelegate);
    QVERIFY(mDelegate->text().isEmpty());

    auto mRsvp = w.findChild<QCheckBox *>(QStringLiteral("informcheckbox"));
    QVERIFY(mRsvp);
    QVERIFY(mRsvp->isChecked());
    QVERIFY(!mRsvp->text().isEmpty());

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QPushButton *mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    QVERIFY(mOkButton);
    QVERIFY(!mOkButton->isEnabled());
}

void DelegateSelectorTest::shouldChangeOkButtonState()
{
    DelegateSelector w;
    auto mDelegate = w.findChild<PimCommon::AddresseeLineEdit *>(QStringLiteral("delegate"));
    mDelegate->setEnableAkonadiSearch(false);
    mDelegate->setEnableBalooSearch(false);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
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
    auto mRsvp = w.findChild<QCheckBox *>(QStringLiteral("informcheckbox"));
    QVERIFY(mRsvp->isChecked());
    mRsvp->setChecked(true);
    QVERIFY(w.rsvp());

    mRsvp->setChecked(false);
    QVERIFY(!w.rsvp());
}

QTEST_MAIN(DelegateSelectorTest)

#include "moc_delegateselectortest.cpp"

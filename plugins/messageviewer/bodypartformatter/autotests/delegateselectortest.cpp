/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

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
using namespace Qt::Literals::StringLiterals;

DelegateSelectorTest::DelegateSelectorTest(QObject *parent)
    : QObject(parent)
{
}

DelegateSelectorTest::~DelegateSelectorTest() = default;

void DelegateSelectorTest::shouldHaveDefaultValue()
{
    DelegateSelector w;
    const auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    const auto mDelegate = w.findChild<PimCommon::AddresseeLineEdit *>(u"delegate"_s);
    QVERIFY(mDelegate);
    QVERIFY(mDelegate->text().isEmpty());

    const auto mRsvp = w.findChild<QCheckBox *>(u"informcheckbox"_s);
    QVERIFY(mRsvp);
    QVERIFY(mRsvp->isChecked());
    QVERIFY(!mRsvp->text().isEmpty());

    const auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    QPushButton *mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    QVERIFY(mOkButton);
    QVERIFY(!mOkButton->isEnabled());
}

void DelegateSelectorTest::shouldChangeOkButtonState()
{
    DelegateSelector w;
    const auto mDelegate = w.findChild<PimCommon::AddresseeLineEdit *>(u"delegate"_s);
    mDelegate->setEnableAkonadiSearch(false);
    mDelegate->setEnableBalooSearch(false);

    const auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QPushButton *mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    QVERIFY(!mOkButton->isEnabled());

    mDelegate->setText(u"foo"_s);
    QVERIFY(mOkButton->isEnabled());

    mDelegate->clear();
    QVERIFY(!mOkButton->isEnabled());
    mDelegate->setText(u" "_s);
    QVERIFY(!mOkButton->isEnabled());
}

void DelegateSelectorTest::shouldReturnCheckBoxState()
{
    DelegateSelector w;
    const auto mRsvp = w.findChild<QCheckBox *>(u"informcheckbox"_s);
    QVERIFY(mRsvp->isChecked());
    mRsvp->setChecked(true);
    QVERIFY(w.rsvp());

    mRsvp->setChecked(false);
    QVERIFY(!w.rsvp());
}

QTEST_MAIN(DelegateSelectorTest)

#include "moc_delegateselectortest.cpp"

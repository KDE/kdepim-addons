/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretabwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "../confirmaddressconfiguretabwidget.h"
#include <PimCommon/SimpleStringListEditor>
#include <QGroupBox>
#include <QRadioButton>
#include <QTest>
#include <QVBoxLayout>

ConfirmAddressConfigureTabWidgetTest::ConfirmAddressConfigureTabWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ConfirmAddressConfigureTabWidgetTest::~ConfirmAddressConfigureTabWidgetTest() = default;

void ConfirmAddressConfigureTabWidgetTest::shouldHaveDefaultValue()
{
    ConfirmAddressConfigureTabWidget w;
    auto groupBoxDomainName = w.findChild<QGroupBox *>(u"groupboxdomainname"_s);
    QVERIFY(groupBoxDomainName);
    auto layoutDomainName = w.findChild<QVBoxLayout *>(u"layoutdomainname"_s);
    QVERIFY(layoutDomainName);

    auto mAcceptedDomain = w.findChild<QRadioButton *>(u"acceptdomainname"_s);
    QVERIFY(mAcceptedDomain);
    QVERIFY(!mAcceptedDomain->text().isEmpty());

    auto mRejectedDomain = w.findChild<QRadioButton *>(u"rejectdomainname"_s);
    QVERIFY(mRejectedDomain);
    QVERIFY(!mRejectedDomain->text().isEmpty());

    auto mDomainNameListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(u"domainnamelisteditor"_s);
    QVERIFY(mDomainNameListEditor);

    auto groupBoxWhiteList = w.findChild<QGroupBox *>(u"groupboxwhitelist"_s);
    QVERIFY(groupBoxWhiteList);
    auto layoutWhiteList = w.findChild<QVBoxLayout *>(u"layoutwhitelist"_s);
    QVERIFY(layoutWhiteList);
    auto mWhiteListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(u"whitelisteditor"_s);
    QVERIFY(mWhiteListEditor);
}

QTEST_MAIN(ConfirmAddressConfigureTabWidgetTest)

#include "moc_confirmaddressconfiguretabwidgettest.cpp"

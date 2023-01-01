/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretabwidgettest.h"
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
    auto groupBoxDomainName = w.findChild<QGroupBox *>(QStringLiteral("groupboxdomainname"));
    QVERIFY(groupBoxDomainName);
    auto layoutDomainName = w.findChild<QVBoxLayout *>(QStringLiteral("layoutdomainname"));
    QVERIFY(layoutDomainName);

    auto mAcceptedDomain = w.findChild<QRadioButton *>(QStringLiteral("acceptdomainname"));
    QVERIFY(mAcceptedDomain);
    QVERIFY(!mAcceptedDomain->text().isEmpty());

    auto mRejectedDomain = w.findChild<QRadioButton *>(QStringLiteral("rejectdomainname"));
    QVERIFY(mRejectedDomain);
    QVERIFY(!mRejectedDomain->text().isEmpty());

    auto mDomainNameListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(QStringLiteral("domainnamelisteditor"));
    QVERIFY(mDomainNameListEditor);

    auto groupBoxWhiteList = w.findChild<QGroupBox *>(QStringLiteral("groupboxwhitelist"));
    QVERIFY(groupBoxWhiteList);
    auto layoutWhiteList = w.findChild<QVBoxLayout *>(QStringLiteral("layoutwhitelist"));
    QVERIFY(layoutWhiteList);
    auto mWhiteListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(QStringLiteral("whitelisteditor"));
    QVERIFY(mWhiteListEditor);
}

QTEST_MAIN(ConfirmAddressConfigureTabWidgetTest)

/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretabwidgettest.h"
#include "../confirmaddressconfiguretabwidget.h"
#include <QTest>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <PimCommon/SimpleStringListEditor>

ConfirmAddressConfigureTabWidgetTest::ConfirmAddressConfigureTabWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ConfirmAddressConfigureTabWidgetTest::~ConfirmAddressConfigureTabWidgetTest()
{
}

void ConfirmAddressConfigureTabWidgetTest::shouldHaveDefaultValue()
{
    ConfirmAddressConfigureTabWidget w;
    QGroupBox *groupBoxDomainName = w.findChild<QGroupBox *>(QStringLiteral("groupboxdomainname"));
    QVERIFY(groupBoxDomainName);
    QVBoxLayout *layoutDomainName = w.findChild<QVBoxLayout *>(QStringLiteral("layoutdomainname"));
    QVERIFY(layoutDomainName);

    QRadioButton *mAcceptedDomain = w.findChild<QRadioButton *>(QStringLiteral("acceptdomainname"));
    QVERIFY(mAcceptedDomain);
    QVERIFY(!mAcceptedDomain->text().isEmpty());

    QRadioButton *mRejectedDomain = w.findChild<QRadioButton *>(QStringLiteral("rejectdomainname"));
    QVERIFY(mRejectedDomain);
    QVERIFY(!mRejectedDomain->text().isEmpty());

    PimCommon::SimpleStringListEditor *mDomainNameListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(QStringLiteral("domainnamelisteditor"));
    QVERIFY(mDomainNameListEditor);

    QGroupBox *groupBoxWhiteList = w.findChild<QGroupBox *>(QStringLiteral("groupboxwhitelist"));
    QVERIFY(groupBoxWhiteList);
    QVBoxLayout *layoutWhiteList = w.findChild<QVBoxLayout *>(QStringLiteral("layoutwhitelist"));
    QVERIFY(layoutWhiteList);
    PimCommon::SimpleStringListEditor *mWhiteListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(QStringLiteral("whitelisteditor"));
    QVERIFY(mWhiteListEditor);
}

QTEST_MAIN(ConfirmAddressConfigureTabWidgetTest)

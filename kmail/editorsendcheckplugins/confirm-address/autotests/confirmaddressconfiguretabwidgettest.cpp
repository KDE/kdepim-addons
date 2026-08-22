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
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

ConfirmAddressConfigureTabWidgetTest::ConfirmAddressConfigureTabWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressConfigureTabWidgetTest::~ConfirmAddressConfigureTabWidgetTest() = default;

void ConfirmAddressConfigureTabWidgetTest::shouldHaveDefaultValue()
{
    ConfirmAddressConfigureTabWidget w;
    const auto groupBoxDomainName = w.findChild<QGroupBox *>(u"groupboxdomainname"_s);
    QVERIFY(groupBoxDomainName);
    const auto layoutDomainName = w.findChild<QVBoxLayout *>(u"layoutdomainname"_s);
    QVERIFY(layoutDomainName);

    const auto mAcceptedDomain = w.findChild<QRadioButton *>(u"acceptdomainname"_s);
    QVERIFY(mAcceptedDomain);
    QVERIFY(!mAcceptedDomain->text().isEmpty());

    const auto mRejectedDomain = w.findChild<QRadioButton *>(u"rejectdomainname"_s);
    QVERIFY(mRejectedDomain);
    QVERIFY(!mRejectedDomain->text().isEmpty());

    const auto mDomainNameListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(u"domainnamelisteditor"_s);
    QVERIFY(mDomainNameListEditor);

    const auto groupBoxWhiteList = w.findChild<QGroupBox *>(u"groupboxwhitelist"_s);
    QVERIFY(groupBoxWhiteList);
    const auto layoutWhiteList = w.findChild<QVBoxLayout *>(u"layoutwhitelist"_s);
    QVERIFY(layoutWhiteList);
    const auto mWhiteListEditor = w.findChild<PimCommon::SimpleStringListEditor *>(u"whitelisteditor"_s);
    QVERIFY(mWhiteListEditor);
}

QTEST_MAIN(ConfirmAddressConfigureTabWidgetTest)

#include "moc_confirmaddressconfiguretabwidgettest.cpp"

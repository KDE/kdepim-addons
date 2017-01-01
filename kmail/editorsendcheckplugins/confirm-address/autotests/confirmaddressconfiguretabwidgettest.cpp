/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#include "confirmaddressconfiguretabwidgettest.h"
#include "../confirmaddressconfiguretabwidget.h"
#include <QTest>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <PimCommon/SimpleStringlistEditor>

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

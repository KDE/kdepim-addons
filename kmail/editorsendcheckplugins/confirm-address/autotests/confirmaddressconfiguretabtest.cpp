/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretabtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../confirmaddressconfiguretab.h"
#include <QTabWidget>
#include <QTest>
#include <QVBoxLayout>

ConfirmAddressConfigureTabTest::ConfirmAddressConfigureTabTest(QObject *parent)
    : QObject(parent)
{
}

ConfirmAddressConfigureTabTest::~ConfirmAddressConfigureTabTest() = default;

void ConfirmAddressConfigureTabTest::shouldHaveDefaultValue()
{
    ConfirmAddressConfigureTab w(nullptr);
    auto vboxlayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(vboxlayout);
    QCOMPARE(vboxlayout->contentsMargins(), QMargins());

    auto mTabWidget = w.findChild<QTabWidget *>(u"tabwidget"_s);
    QVERIFY(mTabWidget);
}

QTEST_MAIN(ConfirmAddressConfigureTabTest)

#include "moc_confirmaddressconfiguretabtest.cpp"

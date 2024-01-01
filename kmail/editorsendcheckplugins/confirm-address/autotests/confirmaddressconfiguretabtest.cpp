/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretabtest.h"
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
    auto vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);
    QCOMPARE(vboxlayout->contentsMargins(), QMargins());

    auto mTabWidget = w.findChild<QTabWidget *>(QStringLiteral("tabwidget"));
    QVERIFY(mTabWidget);
}

QTEST_MAIN(ConfirmAddressConfigureTabTest)

#include "moc_confirmaddressconfiguretabtest.cpp"

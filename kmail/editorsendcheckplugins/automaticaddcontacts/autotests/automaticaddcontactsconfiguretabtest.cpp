/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfiguretabtest.h"
#include "../automaticaddcontactsconfiguretab.h"
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>

AutomaticAddContactsConfigureTabTest::AutomaticAddContactsConfigureTabTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AutomaticAddContactsConfigureTabTest::~AutomaticAddContactsConfigureTabTest() = default;

void AutomaticAddContactsConfigureTabTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsConfigureTab w(nullptr);
    auto vboxlayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);
    QCOMPARE(vboxlayout->contentsMargins(), QMargins(0, 0, 0, 0));
    auto mTabWidget = w.findChild<QTabWidget *>(QStringLiteral("tabwidget"));
    QVERIFY(mTabWidget);
}

QTEST_MAIN(AutomaticAddContactsConfigureTabTest)

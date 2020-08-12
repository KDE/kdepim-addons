/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfiguretabtest.h"
#include "../automaticaddcontactsconfiguretab.h"
#include <QTest>
#include <QStandardPaths>
#include <QHBoxLayout>
#include <QTabWidget>

AutomaticAddContactsConfigureTabTest::AutomaticAddContactsConfigureTabTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AutomaticAddContactsConfigureTabTest::~AutomaticAddContactsConfigureTabTest()
{
}

void AutomaticAddContactsConfigureTabTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsConfigureTab w(nullptr);
    QHBoxLayout *vboxlayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);
    QCOMPARE(vboxlayout->contentsMargins(), QMargins(0, 0, 0, 0));
    QTabWidget *mTabWidget = w.findChild<QTabWidget *>(QStringLiteral("tabwidget"));
    QVERIFY(mTabWidget);
}

QTEST_MAIN(AutomaticAddContactsConfigureTabTest)

/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguretabtest.h"
#include "../dkimconfiguretab.h"
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>
QTEST_MAIN(DKIMConfigureTabTest)

DKIMConfigureTabTest::DKIMConfigureTabTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void DKIMConfigureTabTest::shouldHaveDefaultValue()
{
    DKIMConfigureTab w;

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTabWidget = w.findChild<QTabWidget *>(QStringLiteral("tabwidget"));
    QVERIFY(mTabWidget);
}

#include "moc_dkimconfiguretabtest.cpp"

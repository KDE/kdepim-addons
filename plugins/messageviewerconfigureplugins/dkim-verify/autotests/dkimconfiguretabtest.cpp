/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguretabtest.h"
#include "../dkimconfiguretab.h"
#include <QHBoxLayout>
#include <QTabWidget>
#include <QTest>
QTEST_MAIN(DKIMConfigureTabTest)

DKIMConfigureTabTest::DKIMConfigureTabTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMConfigureTabTest::shouldHaveDefaultValue()
{
    DKIMConfigureTab w;

    QHBoxLayout *mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QTabWidget *mTabWidget = w.findChild<QTabWidget *>(QStringLiteral("tabwidget"));
    QVERIFY(mTabWidget);
}

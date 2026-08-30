/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguretabtest.h"
#include "../dkimconfiguretab.h"
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(DKIMConfigureTabTest)

DKIMConfigureTabTest::DKIMConfigureTabTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void DKIMConfigureTabTest::shouldHaveDefaultValue()
{
    DKIMConfigureTab w;

    const auto mainLayout = w.findChild<QHBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mTabWidget = w.findChild<QTabWidget *>(u"tabwidget"_s);
    QVERIFY(mTabWidget);
}

#include "moc_dkimconfiguretabtest.cpp"

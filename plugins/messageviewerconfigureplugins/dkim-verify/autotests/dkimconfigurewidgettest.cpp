/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfigurewidgettest.h"
#include "../dkimconfiguretab.h"
#include "../dkimconfigurewidget.h"
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(DKIMConfigureWidgetTest)

DKIMConfigureWidgetTest::DKIMConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMConfigureWidgetTest::shouldHaveDefaultValue()
{
    DKIMConfigureWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTabWidget = w.findChild<DKIMConfigureTab *>(QStringLiteral("tabwidget"));
    QVERIFY(mTabWidget);
}

#include "moc_dkimconfigurewidgettest.cpp"

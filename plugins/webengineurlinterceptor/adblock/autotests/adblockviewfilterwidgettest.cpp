/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "adblockviewfilterwidgettest.h"
#include "adblockviewfilterwidget.h"
#include <QTest>

QTEST_MAIN(AdblockViewFilterWidgetTest)
AdblockViewFilterWidgetTest::AdblockViewFilterWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockViewFilterWidgetTest::shouldHaveDefaultValues()
{
    AdblockViewFilterWidget w;
    // TODO
}

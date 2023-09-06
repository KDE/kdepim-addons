/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterwidgettest.h"
#include "adblockfilterwidget.h"
#include <QTest>
QTEST_MAIN(AdblockFilterWidgetTest)

AdblockFilterWidgetTest::AdblockFilterWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockFilterWidgetTest::shouldHaveDefaultValues()
{
    AdblockFilterWidget w;
    // TODO
}

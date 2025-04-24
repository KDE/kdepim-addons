/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskwidgettest.h"
#include "autogenerateconfigureaskwidget.h"
#include <QTest>

QTEST_MAIN(AutogenerateConfigureAskWidgetTest)

AutogenerateConfigureAskWidgetTest::AutogenerateConfigureAskWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AutogenerateConfigureAskWidgetTest::shouldHaveDefaultValues()
{
    // TODO
    AutogenerateConfigureAskWidget w;
}

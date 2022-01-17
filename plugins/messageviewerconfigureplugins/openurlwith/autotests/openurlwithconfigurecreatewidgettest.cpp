/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatewidgettest.h"
#include "openurlwithconfigurecreatewidget.h"
#include <QTest>
QTEST_MAIN(OpenUrlWithConfigureCreateWidgetTest)
OpenUrlWithConfigureCreateWidgetTest::OpenUrlWithConfigureCreateWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureCreateWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureCreateWidget w;
}

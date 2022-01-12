/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurewidgettest.h"
#include "openurlwithconfigurewidget.h"
#include <QTest>
QTEST_MAIN(OpenUrlWithConfigureWidgetTest)
OpenUrlWithConfigureWidgetTest::OpenUrlWithConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureWidget w;
    // TODO
}

/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidgettest.h"
#include "confirmbeforedeletingwidget.h"
#include <QTest>
QTEST_MAIN(ConfirmBeforeDeletingWidgetTest)

ConfirmBeforeDeletingWidgetTest::ConfirmBeforeDeletingWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingWidgetTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingWidget w;
    // TODO
}

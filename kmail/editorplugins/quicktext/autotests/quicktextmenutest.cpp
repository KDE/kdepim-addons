/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextmenutest.h"
#include "../quicktextmenu.h"
#include <QTest>

QTEST_MAIN(QuickTextMenuTest)

QuickTextMenuTest::QuickTextMenuTest(QObject *parent)
    : QObject(parent)
{
}

void QuickTextMenuTest::shouldHaveDefaultValues()
{
    QuickTextMenu m(nullptr);
    QVERIFY(m.menu());
}

/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingruletest.h"
#include "confirmbeforedeletingrule.h"
#include <QTest>
QTEST_GUILESS_MAIN(ConfirmBeforeDeletingRuleTest)

ConfirmBeforeDeletingRuleTest::ConfirmBeforeDeletingRuleTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingRuleTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingRule r;
    QVERIFY(r.pattern().isEmpty());
    // TODO
}

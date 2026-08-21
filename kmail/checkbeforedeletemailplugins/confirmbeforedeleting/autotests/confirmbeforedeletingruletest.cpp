/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingruletest.h"
#include "confirmbeforedeletingrule.h"
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(ConfirmBeforeDeletingRuleTest)
using namespace Qt::Literals::StringLiterals;
ConfirmBeforeDeletingRuleTest::ConfirmBeforeDeletingRuleTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void ConfirmBeforeDeletingRuleTest::shouldHaveDefaultValues()
{
    const ConfirmBeforeDeletingRule r;
    QVERIFY(r.pattern().isEmpty());
    QVERIFY(!r.isValid());
    QCOMPARE(r.ruleType(), ConfirmBeforeDeletingRule::RuleType::Unknown);
    // TODO
}

void ConfirmBeforeDeletingRuleTest::shouldBeEqual()
{
    ConfirmBeforeDeletingRule r;
    r.setPattern(u"foo"_s);
    r.setRuleType(ConfirmBeforeDeletingRule::RuleType::Body);
    {
        ConfirmBeforeDeletingRule r1;
        QVERIFY(r != r1);
    }
    {
        ConfirmBeforeDeletingRule r1;
        r.setPattern(u"foo"_s);
        QVERIFY(r != r1);
    }
    {
        ConfirmBeforeDeletingRule r1;
        r1.setPattern(u"foo"_s);
        r1.setRuleType(ConfirmBeforeDeletingRule::RuleType::Body);
        QVERIFY(r == r1);
    }
}
#include "moc_confirmbeforedeletingruletest.cpp"

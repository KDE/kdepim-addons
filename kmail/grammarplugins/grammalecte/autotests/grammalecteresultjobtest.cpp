/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultjobtest.h"
#include "grammalecteresultjob.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GrammarResultJobTest)
GrammarResultJobTest::GrammarResultJobTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammarResultJobTest::shouldHaveDefaultValue()
{
    GrammalecteResultJob job;
    QVERIFY(!job.canStart());
    QVERIFY(job.text().isEmpty());
    QVERIFY(job.pythonPath().isEmpty());
    QVERIFY(job.grammarlecteCliPath().isEmpty());
    QVERIFY(job.arguments().isEmpty());
}

void GrammarResultJobTest::shouldBeAbleToStart()
{
    GrammalecteResultJob job;
    // Args can be empty if we use default values
    QVERIFY(!job.canStart());
    job.setText(QStringLiteral("ff"));
    QVERIFY(!job.canStart());
    job.setPythonPath(QStringLiteral("ff"));
    QVERIFY(!job.canStart());
    job.setGrammarlecteCliPath(QStringLiteral("ff"));
    QVERIFY(job.canStart());

    job.setArguments(QStringList() << QStringLiteral("ff"));
    QVERIFY(job.canStart());
}

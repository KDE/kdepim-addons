/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectegenerateconfigoptionjobtest.h"
#include "grammalectegenerateconfigoptionjob.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GrammalecteGenerateConfigOptionJobTest)

GrammalecteGenerateConfigOptionJobTest::GrammalecteGenerateConfigOptionJobTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteGenerateConfigOptionJobTest::shouldHaveDefaultValue()
{
    GrammalecteGenerateConfigOptionJob job;
    QVERIFY(!job.canStart());

    GrammalecteGenerateConfigOptionJob::Option opt;
    QVERIFY(opt.optionName.isEmpty());
    QVERIFY(opt.description.isEmpty());
    QVERIFY(!opt.defaultValue);
}

void GrammalecteGenerateConfigOptionJobTest::shouldBeAbleToStart()
{
    GrammalecteGenerateConfigOptionJob job;
    QVERIFY(!job.canStart());
    job.setPythonPath(QStringLiteral("ff"));
    QVERIFY(!job.canStart());
    job.setGrammarlecteCliPath(QStringLiteral("ff"));
    QVERIFY(job.canStart());
}

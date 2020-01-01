/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "grammalecteresultjobtest.h"
#include "grammalecteresultjob.h"
#include <QTest>
#include <QStandardPaths>
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
    //Args can be empty if we use default values
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

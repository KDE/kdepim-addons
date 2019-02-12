/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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


#include "languagetoolresultjobtest.h"
#include "languagetoolresultjob.h"
#include <QTest>
QTEST_MAIN(LanguagetoolResultJobTest)
LanguagetoolResultJobTest::LanguagetoolResultJobTest(QObject *parent)
    : QObject(parent)
{

}

void LanguagetoolResultJobTest::shouldHaveDefaultValue()
{
   LanguagetoolResultJob job;
   QVERIFY(!job.networkAccessManager());
   QVERIFY(job.arguments().isEmpty());
   QVERIFY(!job.canStart());
   QVERIFY(job.text().isEmpty());
   QVERIFY(job.url().isEmpty());
   QVERIFY(job.language().isEmpty());
}

void LanguagetoolResultJobTest::shouldBeAbleToStart()
{
    LanguagetoolResultJob job;
    QVERIFY(!job.canStart());
    job.setText(QStringLiteral("foo"));
    QVERIFY(!job.canStart());
    job.setUrl(QStringLiteral("http://www.kde.org"));
    QVERIFY(!job.canStart());
    job.setLanguage(QStringLiteral("foo"));
    QVERIFY(!job.canStart());
    QNetworkAccessManager network;
    job.setNetworkAccessManager(&network);
    QVERIFY(job.canStart());
    job.setText(QStringLiteral(" "));
    QVERIFY(!job.canStart());
    job.setText(QStringLiteral(" DDDD"));
    QVERIFY(job.canStart());
}

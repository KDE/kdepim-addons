/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "checkattachmentjobtest.h"
#include "../sendattachments/checkattachmentjob.h"

#include <QTest>

CheckAttachmentJobTest::CheckAttachmentJobTest(QObject *parent)
    : QObject(parent)
{

}

CheckAttachmentJobTest::~CheckAttachmentJobTest()
{

}

void CheckAttachmentJobTest::shouldHaveDefaultValue()
{
    CheckAttachmentJob job;
    QVERIFY(job.resultList().isEmpty());
    QVERIFY(job.originalEmails().isEmpty());

    job.start();
    QVERIFY(job.resultList().isEmpty());
    QVERIFY(job.originalEmails().isEmpty());
}

void CheckAttachmentJobTest::shouldAssignEmails()
{
    CheckAttachmentJob job;
    const QStringList lst{ QStringLiteral("foo"), QStringLiteral("bla") };
    job.setOriginalEmails(lst);
    QCOMPARE(job.originalEmails(), lst);
}

QTEST_MAIN(CheckAttachmentJobTest)

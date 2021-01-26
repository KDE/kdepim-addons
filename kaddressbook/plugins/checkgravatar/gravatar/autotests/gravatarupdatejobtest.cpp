/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarupdatejobtest.h"
#include "../job/gravatarupdatejob.h"
#include <QTest>

GravatarUpdateJobTest::GravatarUpdateJobTest(QObject *parent)
    : QObject(parent)
{
}

GravatarUpdateJobTest::~GravatarUpdateJobTest()
{
}

void GravatarUpdateJobTest::shouldHaveDefaultValue()
{
    KABGravatar::GravatarUpdateJob job;
    QVERIFY(job.email().isEmpty());
    QVERIFY(!job.item().isValid());
}

QTEST_MAIN(GravatarUpdateJobTest)

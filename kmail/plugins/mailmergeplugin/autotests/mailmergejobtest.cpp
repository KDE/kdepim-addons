/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergejobtest.h"
#include <QTest>
MailMergeJobTest::MailMergeJobTest(QObject *parent)
    : QObject(parent)
{
}

MailMergeJobTest::~MailMergeJobTest()
{
}

QTEST_MAIN(MailMergeJobTest)

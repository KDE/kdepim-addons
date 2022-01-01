/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergejobtest.h"
#include <QTest>
MailMergeJobTest::MailMergeJobTest(QObject *parent)
    : QObject(parent)
{
}

MailMergeJobTest::~MailMergeJobTest() = default;

QTEST_MAIN(MailMergeJobTest)

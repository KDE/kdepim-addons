/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

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

#include "moc_mailmergejobtest.cpp"

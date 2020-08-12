/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsjobtest.h"
#include <QTest>
#include <QStandardPaths>

AutomaticAddContactsJobTest::AutomaticAddContactsJobTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AutomaticAddContactsJobTest::~AutomaticAddContactsJobTest()
{
}

QTEST_MAIN(AutomaticAddContactsJobTest)

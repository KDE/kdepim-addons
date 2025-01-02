/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsjobtest.h"
#include <QStandardPaths>
#include <QTest>

AutomaticAddContactsJobTest::AutomaticAddContactsJobTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AutomaticAddContactsJobTest::~AutomaticAddContactsJobTest() = default;

QTEST_MAIN(AutomaticAddContactsJobTest)

#include "moc_automaticaddcontactsjobtest.cpp"

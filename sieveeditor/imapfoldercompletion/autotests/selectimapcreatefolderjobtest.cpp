/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapcreatefolderjobtest.h"

#include <QTest>

SelectImapCreateJobTest::SelectImapCreateJobTest(QObject *parent)
    : QObject(parent)
{
}

SelectImapCreateJobTest::~SelectImapCreateJobTest() = default;

QTEST_MAIN(SelectImapCreateJobTest)

#include "moc_selectimapcreatefolderjobtest.cpp"

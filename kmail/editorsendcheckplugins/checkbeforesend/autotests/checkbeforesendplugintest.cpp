/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendplugintest.h"
#include "../checkbeforesendplugin.h"
#include <QTest>

CheckBeforeSendPluginTest::CheckBeforeSendPluginTest(QObject *parent)
    : QObject(parent)
{
}

CheckBeforeSendPluginTest::~CheckBeforeSendPluginTest() = default;

void CheckBeforeSendPluginTest::shouldHaveDefaultValue()
{
    CheckBeforeSendPlugin plugin;
    QVERIFY(plugin.hasConfigureDialog());
    QVERIFY(plugin.createInterface(this));
}

QTEST_MAIN(CheckBeforeSendPluginTest)

#include "moc_checkbeforesendplugintest.cpp"

/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "automaticaddcontactsplugintest.h"
#include "../automaticaddcontactsplugin.h"

#include <QTest>

AutomaticAddContactsPluginTest::AutomaticAddContactsPluginTest(QObject *parent)
    : QObject(parent)
{
}

AutomaticAddContactsPluginTest::~AutomaticAddContactsPluginTest()
{
}

void AutomaticAddContactsPluginTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsPlugin plugin;
    QVERIFY(plugin.hasConfigureDialog());
    QVERIFY(plugin.createInterface(this));
}

QTEST_MAIN(AutomaticAddContactsPluginTest)

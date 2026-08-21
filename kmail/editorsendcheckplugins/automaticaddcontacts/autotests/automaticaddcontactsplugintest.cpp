/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "automaticaddcontactsplugintest.h"
#include "../automaticaddcontactsplugin.h"

#include <QStandardPaths>
#include <QTest>

AutomaticAddContactsPluginTest::AutomaticAddContactsPluginTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AutomaticAddContactsPluginTest::~AutomaticAddContactsPluginTest() = default;

void AutomaticAddContactsPluginTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsPlugin plugin;
    QVERIFY(plugin.hasConfigureDialog());
    QVERIFY(plugin.createInterface(this));
}

QTEST_MAIN(AutomaticAddContactsPluginTest)

#include "moc_automaticaddcontactsplugintest.cpp"

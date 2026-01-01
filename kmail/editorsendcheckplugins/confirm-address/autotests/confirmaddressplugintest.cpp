/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressplugintest.h"
#include "../confirmaddressplugin.h"
#include <QStandardPaths>
#include <QTest>

ConfirmAddressPluginTest::ConfirmAddressPluginTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressPluginTest::~ConfirmAddressPluginTest() = default;

void ConfirmAddressPluginTest::shouldHaveDefaultValue()
{
    ConfirmAddressPlugin plugin;
    QVERIFY(plugin.hasConfigureDialog());
    QVERIFY(plugin.createInterface(this));
}

QTEST_MAIN(ConfirmAddressPluginTest)

#include "moc_confirmaddressplugintest.cpp"

/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressplugintest.h"
#include "../confirmaddressplugin.h"
#include <QTest>
#include <QStandardPaths>

ConfirmAddressPluginTest::ConfirmAddressPluginTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressPluginTest::~ConfirmAddressPluginTest()
{
}

void ConfirmAddressPluginTest::shouldHaveDefaultValue()
{
    ConfirmAddressPlugin plugin;
    QVERIFY(plugin.hasConfigureDialog());
    QVERIFY(plugin.createInterface(this));
}

QTEST_MAIN(ConfirmAddressPluginTest)

/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertspecialcharacterplugineditortest.h"
#include "../insertspecialcharacterplugineditor.h"
#include <QTest>

InsertSpecialCharacterPluginEditorTest::InsertSpecialCharacterPluginEditorTest(QObject *parent)
    : QObject(parent)
{
}

InsertSpecialCharacterPluginEditorTest::~InsertSpecialCharacterPluginEditorTest() = default;

void InsertSpecialCharacterPluginEditorTest::shouldHaveDefaultValue()
{
    InsertSpecialCharacterPluginEditor plugin;
    auto interface = plugin.createInterface();
    QVERIFY(interface);
    QVERIFY(!plugin.hasConfigureDialog());
    QVERIFY(!plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasToolBarSupport());
    delete interface;
}

QTEST_MAIN(InsertSpecialCharacterPluginEditorTest)

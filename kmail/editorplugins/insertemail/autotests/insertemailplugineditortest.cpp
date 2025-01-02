/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertemailplugineditortest.h"
#include "../insertemailplugineditor.h"
#include <KActionCollection>
#include <QTest>

InsertEmailPluginEditorTest::InsertEmailPluginEditorTest(QObject *parent)
    : QObject(parent)
{
}

InsertEmailPluginEditorTest::~InsertEmailPluginEditorTest() = default;

void InsertEmailPluginEditorTest::shouldHaveDefaultValue()
{
    InsertEmailPluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
    QVERIFY(!plugin.hasConfigureDialog());
    QVERIFY(!plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasToolBarSupport());
}

QTEST_MAIN(InsertEmailPluginEditorTest)

#include "moc_insertemailplugineditortest.cpp"

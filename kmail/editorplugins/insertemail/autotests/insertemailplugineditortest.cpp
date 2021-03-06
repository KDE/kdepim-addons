/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

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

InsertEmailPluginEditorTest::~InsertEmailPluginEditorTest()
{
}

void InsertEmailPluginEditorTest::shouldHaveDefaultValue()
{
    InsertEmailPluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
    QVERIFY(!plugin.hasConfigureDialog());
    QVERIFY(!plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasToolBarSupport());
}

QTEST_MAIN(InsertEmailPluginEditorTest)

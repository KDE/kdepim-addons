/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "nonbreakingspaceplugineditortest.h"
#include "../nonbreakingspaceplugineditor.h"
#include <KActionCollection>
#include <QTest>

NonBreakingSpacePluginEditorTest::NonBreakingSpacePluginEditorTest(QObject *parent)
    : QObject(parent)
{
}

NonBreakingSpacePluginEditorTest::~NonBreakingSpacePluginEditorTest()
{
}

void NonBreakingSpacePluginEditorTest::shouldHaveDefaultValue()
{
    NonBreakingSpacePluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
    QVERIFY(!plugin.hasConfigureDialog());
    QVERIFY(!plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasToolBarSupport());
}

QTEST_MAIN(NonBreakingSpacePluginEditorTest)

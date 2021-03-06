/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionplugineditortest.h"
#include "../autocorrectionplugineditor.h"
#include <KActionCollection>
#include <QTest>

AutoCorrectionPluginEditorTest::AutoCorrectionPluginEditorTest(QObject *parent)
    : QObject(parent)
{
}

AutoCorrectionPluginEditorTest::~AutoCorrectionPluginEditorTest()
{
}

void AutoCorrectionPluginEditorTest::shouldHaveDefaultValue()
{
    AutoCorrectionPluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
    QVERIFY(!plugin.hasConfigureDialog());
    QVERIFY(!plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasToolBarSupport());
}

QTEST_MAIN(AutoCorrectionPluginEditorTest)

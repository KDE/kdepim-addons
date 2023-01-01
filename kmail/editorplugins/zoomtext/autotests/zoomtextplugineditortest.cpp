/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "zoomtextplugineditortest.h"
#include "../zoomtextplugineditor.h"
#include <KActionCollection>
#include <QTest>

ZoomTextPluginEditorTest::ZoomTextPluginEditorTest(QObject *parent)
    : QObject(parent)
{
}

ZoomTextPluginEditorTest::~ZoomTextPluginEditorTest() = default;

void ZoomTextPluginEditorTest::shouldHaveDefaultValue()
{
    ZoomTextPluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
    QVERIFY(!plugin.hasConfigureDialog());
    QVERIFY(plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasToolBarSupport());
}

QTEST_MAIN(ZoomTextPluginEditorTest)

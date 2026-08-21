/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlplugineditortest.h"
#include "../insertshorturlplugineditor.h"
#include <KActionCollection>
#include <QStandardPaths>
#include <QTest>

InsertShorturlPluginEditorTest::InsertShorturlPluginEditorTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

InsertShorturlPluginEditorTest::~InsertShorturlPluginEditorTest() = default;

void InsertShorturlPluginEditorTest::shouldHaveDefaultValue()
{
    InsertShorturlPluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
    QVERIFY(plugin.hasConfigureDialog());
    QVERIFY(plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasToolBarSupport());
}

QTEST_MAIN(InsertShorturlPluginEditorTest)

#include "moc_insertshorturlplugineditortest.cpp"

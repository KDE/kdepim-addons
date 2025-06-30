/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sharetextplugineditortest.h"
using namespace Qt::Literals::StringLiterals;

#include "../sharetextplugineditor.h"
#include <KActionCollection>
#include <QTest>

ShareTextPluginEditorTest::ShareTextPluginEditorTest(QObject *parent)
    : QObject(parent)
{
}

ShareTextPluginEditorTest::~ShareTextPluginEditorTest() = default;

void ShareTextPluginEditorTest::shouldHaveDefaultValue()
{
    ShareTextPluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
    QVERIFY(!plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasConfigureDialog());
    QVERIFY(!plugin.hasToolBarSupport());
}

QTEST_MAIN(ShareTextPluginEditorTest)

#include "moc_sharetextplugineditortest.cpp"

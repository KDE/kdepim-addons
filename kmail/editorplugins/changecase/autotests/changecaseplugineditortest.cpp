/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "changecaseplugineditortest.h"
#include "../changecaseplugineditor.h"
#include <KActionCollection>
#include <QTest>

ChangeCasePluginEditorTest::ChangeCasePluginEditorTest(QObject *parent)
    : QObject(parent)
{
}

ChangeCasePluginEditorTest::~ChangeCasePluginEditorTest()
{
}

void ChangeCasePluginEditorTest::shouldHaveDefaultValue()
{
    ChangeCasePluginEditor plugin;
    QVERIFY(plugin.createInterface(new KActionCollection(this)));
    QVERIFY(plugin.hasPopupMenuSupport());
    QVERIFY(!plugin.hasConfigureDialog());
    QVERIFY(!plugin.hasToolBarSupport());
}

QTEST_MAIN(ChangeCasePluginEditorTest)

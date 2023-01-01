/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownplugintest.h"
#include "../plugin/markdowninterface.h"
#include "../plugin/markdownplugin.h"
#include <QTest>
QTEST_MAIN(MarkdownPluginTest)

MarkdownPluginTest::MarkdownPluginTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownPluginTest::shouldCreateInterface()
{
    MarkdownPlugin w;
    QVERIFY(w.createInterface(this));
    QVERIFY(w.hasConfigureDialog());
    QVERIFY(w.hasStatusBarSupport());
}

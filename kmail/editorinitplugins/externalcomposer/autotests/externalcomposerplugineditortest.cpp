/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerplugineditortest.h"
#include "../externalcomposerplugineditor.h"
#include <QTest>

ExternalComposerPluginEditorTest::ExternalComposerPluginEditorTest(QObject *parent)
    : QObject(parent)
{
}

void ExternalComposerPluginEditorTest::shouldHaveDefaultValue()
{
    ExternalComposerPluginEditor plugin;
    QVERIFY(plugin.hasConfigureDialog());
    auto interface = plugin.createInterface(nullptr);
    QVERIFY(interface);
    delete interface;
}

QTEST_MAIN(ExternalComposerPluginEditorTest)

#include "moc_externalcomposerplugineditortest.cpp"

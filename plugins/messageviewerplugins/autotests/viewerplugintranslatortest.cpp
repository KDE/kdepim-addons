/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugintranslatortest.h"
#include "../common/translatorplugin/viewerplugintranslator.h"
#include <KActionCollection>
#include <MessageViewer/ViewerPluginInterface>
#include <QHBoxLayout>
#include <QTest>

ViewerPluginTranslatorTest::ViewerPluginTranslatorTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginTranslatorTest::~ViewerPluginTranslatorTest() = default;

void ViewerPluginTranslatorTest::shouldHaveDefaultValue()
{
    auto translator = new MessageViewer::ViewerPluginTranslator(this);
    QVERIFY(!translator->viewerPluginName().isEmpty());
    auto parent = std::make_unique<QWidget>(nullptr);
    parent->setLayout(new QHBoxLayout);

    QVERIFY(translator->createView(parent.get(), new KActionCollection(this)));
}

void ViewerPluginTranslatorTest::shouldCreateAction()
{
    auto translator = new MessageViewer::ViewerPluginTranslator(this);
    QVERIFY(!translator->viewerPluginName().isEmpty());
    auto parent = std::make_unique<QWidget>(nullptr);
    parent->setLayout(new QHBoxLayout);

    MessageViewer::ViewerPluginInterface *interface = translator->createView(parent.get(), new KActionCollection(this));
    QVERIFY(!interface->actions().isEmpty());
}

QTEST_MAIN(ViewerPluginTranslatorTest)

#include "moc_viewerplugintranslatortest.cpp"

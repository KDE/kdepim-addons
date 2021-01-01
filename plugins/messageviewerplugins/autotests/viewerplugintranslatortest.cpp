/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugintranslatortest.h"
#include "../common/translatorplugin/viewerplugintranslator.h"
#include <QTest>
#include <KActionCollection>
#include <QHBoxLayout>
#include <MessageViewer/ViewerPluginInterface>

ViewerPluginTranslatorTest::ViewerPluginTranslatorTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginTranslatorTest::~ViewerPluginTranslatorTest()
{
}

void ViewerPluginTranslatorTest::shouldHaveDefaultValue()
{
    MessageViewer::ViewerPluginTranslator *translator = new MessageViewer::ViewerPluginTranslator(this);
    QVERIFY(!translator->viewerPluginName().isEmpty());
    QWidget *parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);

    QVERIFY(translator->createView(parent, new KActionCollection(this)));
}

void ViewerPluginTranslatorTest::shouldCreateAction()
{
    MessageViewer::ViewerPluginTranslator *translator = new MessageViewer::ViewerPluginTranslator(this);
    QVERIFY(!translator->viewerPluginName().isEmpty());
    QWidget *parent = new QWidget(nullptr);
    parent->setLayout(new QHBoxLayout);

    MessageViewer::ViewerPluginInterface *interface = translator->createView(parent, new KActionCollection(this));
    QVERIFY(!interface->actions().isEmpty());
}

QTEST_MAIN(ViewerPluginTranslatorTest)

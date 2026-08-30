/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditwidgettest.h"
#include "../configuredialog/viewerpluginexternaleditwidget.h"
#include <KUrlRequester>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

ViewerPluginExternalEditWidgetTest::ViewerPluginExternalEditWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalEditWidgetTest::~ViewerPluginExternalEditWidgetTest() = default;

void ViewerPluginExternalEditWidgetTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalEditWidget w;
    const auto mainLayout = w.findChild<QFormLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mName = w.findChild<QLineEdit *>(u"name"_s);
    QVERIFY(mName);

    const auto mDescription = w.findChild<QLineEdit *>(u"description"_s);
    QVERIFY(mDescription);

    const auto mCommandLine = w.findChild<QLineEdit *>(u"commandline"_s);
    QVERIFY(mCommandLine);

    const auto mExecutable = w.findChild<KUrlRequester *>(u"mEditorRequester"_s);
    QVERIFY(mExecutable);

    const auto formatHelp = w.findChild<QLabel *>(u"formatHelp"_s);
    QVERIFY(formatHelp);
}

void ViewerPluginExternalEditWidgetTest::shouldGetSaveInfo_data()
{
    QTest::addColumn<ViewerPluginExternalScriptInfo>("scriptinfo");
    ViewerPluginExternalScriptInfo info;
    info.setCommandLine(u"foo"_s);
    info.setDescription(u"blo"_s);
    info.setExecutable(u"voo"_s);
    info.setName(u"bla"_s);
    QTest::newRow("test1") << info;

    info.setIsReadOnly(true);
    QTest::newRow("test2") << info;

    info.setFileName(u"lili"_s);
    QTest::newRow("test3") << info;
}

void ViewerPluginExternalEditWidgetTest::shouldGetSaveInfo()
{
    QFETCH(ViewerPluginExternalScriptInfo, scriptinfo);
    ViewerPluginExternalEditWidget w;
    w.setScriptInfo(scriptinfo);
    QCOMPARE(scriptinfo, w.scriptInfo());
}

QTEST_MAIN(ViewerPluginExternalEditWidgetTest)

#include "moc_viewerpluginexternaleditwidgettest.cpp"

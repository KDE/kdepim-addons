/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditwidgettest.h"
#include "../configuredialog/viewerpluginexternaleditwidget.h"
#include <KUrlRequester>
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>

ViewerPluginExternalEditWidgetTest::ViewerPluginExternalEditWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalEditWidgetTest::~ViewerPluginExternalEditWidgetTest()
{
}

void ViewerPluginExternalEditWidgetTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalEditWidget w;
    QFormLayout *mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QLineEdit *mName = w.findChild<QLineEdit *>(QStringLiteral("name"));
    QVERIFY(mName);

    QLineEdit *mDescription = w.findChild<QLineEdit *>(QStringLiteral("description"));
    QVERIFY(mDescription);

    QLineEdit *mCommandLine = w.findChild<QLineEdit *>(QStringLiteral("commandline"));
    QVERIFY(mCommandLine);

    auto mExecutable = w.findChild<KUrlRequester *>(QStringLiteral("mEditorRequester"));
    QVERIFY(mExecutable);
}

void ViewerPluginExternalEditWidgetTest::shouldGetSaveInfo_data()
{
    QTest::addColumn<ViewerPluginExternalScriptInfo>("scriptinfo");
    ViewerPluginExternalScriptInfo info;
    info.setCommandLine(QStringLiteral("foo"));
    info.setDescription(QStringLiteral("blo"));
    info.setExecutable(QStringLiteral("voo"));
    info.setName(QStringLiteral("bla"));
    QTest::newRow("test1") << info;

    info.setIsReadOnly(true);
    QTest::newRow("test2") << info;

    info.setFileName(QStringLiteral("lili"));
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

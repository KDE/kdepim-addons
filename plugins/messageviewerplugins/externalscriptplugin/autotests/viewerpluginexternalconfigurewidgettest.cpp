/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalconfigurewidgettest.h"
#include "../configuredialog/viewerpluginexternalconfigurewidget.h"
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

ViewerPluginExternalConfigureWidgetTest::ViewerPluginExternalConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ViewerPluginExternalConfigureWidgetTest::~ViewerPluginExternalConfigureWidgetTest() = default;

void ViewerPluginExternalConfigureWidgetTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalConfigureWidget w;
    const auto label = w.findChild<QLabel *>(u"lab"_s);
    QVERIFY(label);
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"layout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mListExternal = w.findChild<QListWidget *>(u"listexternal"_s);
    QVERIFY(mListExternal);
    QCOMPARE(mListExternal->selectionMode(), QAbstractItemView::SingleSelection);
    QVERIFY(mListExternal->alternatingRowColors());

    const auto mAddScript = w.findChild<QPushButton *>(u"addscript"_s);
    QVERIFY(mAddScript);
    QVERIFY(!mAddScript->text().isEmpty());

    const auto mModifyScript = w.findChild<QPushButton *>(u"modifyscript"_s);
    QVERIFY(mModifyScript);
    QVERIFY(!mModifyScript->text().isEmpty());

    const auto mRemoveScript = w.findChild<QPushButton *>(u"removescript"_s);
    QVERIFY(mRemoveScript);
    QVERIFY(!mRemoveScript->text().isEmpty());
}

QTEST_MAIN(ViewerPluginExternalConfigureWidgetTest)

#include "moc_viewerpluginexternalconfigurewidgettest.cpp"

/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalconfigurewidgettest.h"
#include "../configuredialog/viewerpluginexternalconfigurewidget.h"
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>

ViewerPluginExternalConfigureWidgetTest::ViewerPluginExternalConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalConfigureWidgetTest::~ViewerPluginExternalConfigureWidgetTest() = default;

void ViewerPluginExternalConfigureWidgetTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalConfigureWidget w;
    auto label = w.findChild<QLabel *>(QStringLiteral("lab"));
    QVERIFY(label);
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("layout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mListExternal = w.findChild<QListWidget *>(QStringLiteral("listexternal"));
    QVERIFY(mListExternal);
    QCOMPARE(mListExternal->selectionMode(), QAbstractItemView::SingleSelection);
    QVERIFY(mListExternal->alternatingRowColors());

    auto mAddScript = w.findChild<QPushButton *>(QStringLiteral("addscript"));
    QVERIFY(mAddScript);
    QVERIFY(!mAddScript->text().isEmpty());

    auto mModifyScript = w.findChild<QPushButton *>(QStringLiteral("modifyscript"));
    QVERIFY(mModifyScript);
    QVERIFY(!mModifyScript->text().isEmpty());

    auto mRemoveScript = w.findChild<QPushButton *>(QStringLiteral("removescript"));
    QVERIFY(mRemoveScript);
    QVERIFY(!mRemoveScript->text().isEmpty());
}

QTEST_MAIN(ViewerPluginExternalConfigureWidgetTest)

#include "moc_viewerpluginexternalconfigurewidgettest.cpp"

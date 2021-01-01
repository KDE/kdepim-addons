/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalconfigurewidgettest.h"
#include "../configuredialog/viewerpluginexternalconfigurewidget.h"
#include <QTest>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

ViewerPluginExternalConfigureWidgetTest::ViewerPluginExternalConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

ViewerPluginExternalConfigureWidgetTest::~ViewerPluginExternalConfigureWidgetTest()
{
}

void ViewerPluginExternalConfigureWidgetTest::shouldHaveDefaultValue()
{
    ViewerPluginExternalConfigureWidget w;
    auto *label = w.findChild<QLabel *>(QStringLiteral("lab"));
    QVERIFY(label);
    auto *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("layout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    auto *mListExternal = w.findChild<QListWidget *>(QStringLiteral("listexternal"));
    QVERIFY(mListExternal);
    QCOMPARE(mListExternal->selectionMode(), QAbstractItemView::SingleSelection);

    auto *mAddScript = w.findChild<QPushButton *>(QStringLiteral("addscript"));
    QVERIFY(mAddScript);
    QVERIFY(!mAddScript->text().isEmpty());

    auto *mModifyScript = w.findChild<QPushButton *>(QStringLiteral("modifyscript"));
    QVERIFY(mModifyScript);
    QVERIFY(!mModifyScript->text().isEmpty());

    auto *mRemoveScript = w.findChild<QPushButton *>(QStringLiteral("removescript"));
    QVERIFY(mRemoveScript);
    QVERIFY(!mRemoveScript->text().isEmpty());
}

QTEST_MAIN(ViewerPluginExternalConfigureWidgetTest)

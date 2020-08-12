/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

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
    QLabel *label = w.findChild<QLabel *>(QStringLiteral("lab"));
    QVERIFY(label);
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("layout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QListWidget *mListExternal = w.findChild<QListWidget *>(QStringLiteral("listexternal"));
    QVERIFY(mListExternal);
    QCOMPARE(mListExternal->selectionMode(), QAbstractItemView::SingleSelection);

    QPushButton *mAddScript = w.findChild<QPushButton *>(QStringLiteral("addscript"));
    QVERIFY(mAddScript);
    QVERIFY(!mAddScript->text().isEmpty());

    QPushButton *mModifyScript = w.findChild<QPushButton *>(QStringLiteral("modifyscript"));
    QVERIFY(mModifyScript);
    QVERIFY(!mModifyScript->text().isEmpty());

    QPushButton *mRemoveScript = w.findChild<QPushButton *>(QStringLiteral("removescript"));
    QVERIFY(mRemoveScript);
    QVERIFY(!mRemoveScript->text().isEmpty());
}

QTEST_MAIN(ViewerPluginExternalConfigureWidgetTest)

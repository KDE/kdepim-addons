/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurewidgettest.h"
#include "openurlwithconfigurewidget.h"
#include <QHeaderView>
#include <QTest>
#include <QTreeWidget>
#include <QVBoxLayout>
QTEST_MAIN(OpenUrlWithConfigureWidgetTest)
OpenUrlWithConfigureWidgetTest::OpenUrlWithConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTreeWidget = w.findChild<QTreeWidget *>(QStringLiteral("mTreeWidget"));
    QVERIFY(mTreeWidget);
    QVERIFY(!mTreeWidget->rootIsDecorated());
    QVERIFY(!mTreeWidget->header()->sectionsMovable());
}

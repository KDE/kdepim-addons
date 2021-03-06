/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextwidgettest.h"
#include "quicktexttreewidget.h"
#include "quicktextwidget.h"
#include <MailCommon/SnippetWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QTest>
QTEST_MAIN(QuickTextWidgetTest)
QuickTextWidgetTest::QuickTextWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void QuickTextWidgetTest::shouldHaveDefaultValues()
{
    QuickTextWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(w.contentsMargins(), QMargins(0, 0, 0, 0));

    auto mTreeWidget = w.findChild<QuicktextTreeWidget *>(QStringLiteral("treewidget"));
    QVERIFY(mTreeWidget);

    auto mStackedWidget = w.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(mStackedWidget);
}

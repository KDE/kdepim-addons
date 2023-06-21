/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

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
    QCOMPARE(w.contentsMargins(), QMargins());

    auto mTreeWidget = w.findChild<QuicktextTreeWidget *>(QStringLiteral("treewidget"));
    QVERIFY(mTreeWidget);

    auto mStackedWidget = w.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(mStackedWidget);
}

#include "moc_quicktextwidgettest.cpp"

/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextwidgettest.h"
#include "quicktextwidget.h"
#include "quicktexttreewidget.h"
#include <MailCommon/SnippetWidget>
#include <QTest>
#include <QHBoxLayout>
#include <QStackedWidget>
QTEST_MAIN(QuickTextWidgetTest)
QuickTextWidgetTest::QuickTextWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void QuickTextWidgetTest::shouldHaveDefaultValues()
{
    QuickTextWidget w;
    QHBoxLayout *mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(w.contentsMargins(), QMargins(0, 0, 0, 0));

    QuicktextTreeWidget *mTreeWidget = w.findChild<QuicktextTreeWidget *>(QStringLiteral("treewidget"));
    QVERIFY(mTreeWidget);

    QStackedWidget *mStackedWidget = w.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(mStackedWidget);
}

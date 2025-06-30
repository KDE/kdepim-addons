/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(w.contentsMargins(), QMargins());

    auto mTreeWidget = w.findChild<QuicktextTreeWidget *>(u"treewidget"_s);
    QVERIFY(mTreeWidget);

    auto mStackedWidget = w.findChild<QStackedWidget *>(u"stackedwidget"_s);
    QVERIFY(mStackedWidget);
}

#include "moc_quicktextwidgettest.cpp"

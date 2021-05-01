/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextconfigurewidgettest.h"
#include "quicktextconfigurewidget.h"
#include "quicktextwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(QuickTextConfigureWidgetTest)

QuickTextConfigureWidgetTest::QuickTextConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void QuickTextConfigureWidgetTest::shouldHaveDefaultValues()
{
    QuickTextConfigureWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(w.contentsMargins(), QMargins(0, 0, 0, 0));

    auto mSnippetWidget = w.findChild<QuickTextWidget *>(QStringLiteral("snippetwidget"));
    QVERIFY(mSnippetWidget);
}

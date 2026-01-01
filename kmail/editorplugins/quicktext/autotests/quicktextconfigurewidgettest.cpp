/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(w.contentsMargins(), QMargins());

    auto mSnippetWidget = w.findChild<QuickTextWidget *>(u"snippetwidget"_s);
    QVERIFY(mSnippetWidget);
}

#include "moc_quicktextconfigurewidgettest.cpp"

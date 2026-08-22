/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "quicktextconfigurewidget.h"
#include "quicktextwidget.h"
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(QuickTextConfigureWidgetTest)

QuickTextConfigureWidgetTest::QuickTextConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void QuickTextConfigureWidgetTest::shouldHaveDefaultValues()
{
    QuickTextConfigureWidget w;

    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(w.contentsMargins(), QMargins());

    const auto mSnippetWidget = w.findChild<QuickTextWidget *>(u"snippetwidget"_s);
    QVERIFY(mSnippetWidget);
}

#include "moc_quicktextconfigurewidgettest.cpp"

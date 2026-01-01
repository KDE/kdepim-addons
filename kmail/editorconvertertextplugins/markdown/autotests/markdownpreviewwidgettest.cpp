/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownpreviewwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "markdownpreviewwidget.h"
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>
#include <QWebChannel>
#include <QWebEngineView>
QTEST_MAIN(MarkdownPreviewWidgetTest)

MarkdownPreviewWidgetTest::MarkdownPreviewWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownPreviewWidgetTest::shouldHaveDefaultValue()
{
    MarkdownPreviewWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mWebView = w.findChild<QWebEngineView *>(u"webengine"_s);
    QVERIFY(mWebView);
    QCOMPARE(mWebView->contextMenuPolicy(), Qt::NoContextMenu);

    auto mHoverUrlLabel = w.findChild<QLabel *>(u"mHoverUrlLabel"_s);
    QVERIFY(mHoverUrlLabel);
    QVERIFY(mHoverUrlLabel->text().isEmpty());
}

#include "moc_markdownpreviewwidgettest.cpp"

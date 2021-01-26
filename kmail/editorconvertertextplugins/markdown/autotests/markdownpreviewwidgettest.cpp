/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownpreviewwidgettest.h"
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
    auto *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    auto *mWebView = w.findChild<QWebEngineView *>(QStringLiteral("webengine"));
    QVERIFY(mWebView);
    QCOMPARE(mWebView->contextMenuPolicy(), Qt::NoContextMenu);

    auto *mHoverUrlLabel = w.findChild<QLabel *>(QStringLiteral("mHoverUrlLabel"));
    QVERIFY(mHoverUrlLabel);
    QVERIFY(mHoverUrlLabel->text().isEmpty());
}

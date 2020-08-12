/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownpreviewwidgettest.h"
#include "markdownpreviewwidget.h"
#include <QVBoxLayout>
#include <QTest>
#include <QLabel>
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
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QWebEngineView *mWebView = w.findChild<QWebEngineView *>(QStringLiteral("webengine"));
    QVERIFY(mWebView);
    QCOMPARE(mWebView->contextMenuPolicy(), Qt::NoContextMenu);

    QLabel *mHoverUrlLabel = w.findChild<QLabel *>(QStringLiteral("mHoverUrlLabel"));
    QVERIFY(mHoverUrlLabel);
    QVERIFY(mHoverUrlLabel->text().isEmpty());
}

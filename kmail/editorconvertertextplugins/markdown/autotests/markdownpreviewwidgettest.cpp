/*
   Copyright (C) 2018-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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

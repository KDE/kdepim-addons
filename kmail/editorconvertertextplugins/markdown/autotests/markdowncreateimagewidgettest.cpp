/*
    Copyright (C) 2019 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "markdowncreateimagewidgettest.h"
#include "markdowncreateimagewidget.h"
#include "kdepimtest_layout.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(MarkdownCreateImageWidgetTest)

MarkdownCreateImageWidgetTest::MarkdownCreateImageWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownCreateImageWidgetTest::shouldHaveDefaultValue()
{
    MarkdownCreateImageWidget w;

    QFormLayout *mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    KdepimTestLayout::checkContentsMargins(0, mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QLineEdit *mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    QVERIFY(mTitle);
    QVERIFY(mTitle->text().isEmpty());

    QLineEdit *mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    QVERIFY(mLink);
    QVERIFY(mLink->text().isEmpty());
}

void MarkdownCreateImageWidgetTest::shouldGenerateLink()
{
    MarkdownCreateImageWidget w;
    QLineEdit *mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    QLineEdit *mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    mLink->setText(QStringLiteral("http://www.kde.org"));
    mTitle->setText(QStringLiteral("TITLE"));
    QCOMPARE(w.linkStr(), QStringLiteral("![TITLE](http://www.kde.org)"));
}

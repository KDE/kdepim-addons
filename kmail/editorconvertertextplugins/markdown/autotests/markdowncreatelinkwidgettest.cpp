/*
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreatelinkwidgettest.h"
#include "markdowncreatelinkwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(MarkdownCreateLinkWidgetTest)

MarkdownCreateLinkWidgetTest::MarkdownCreateLinkWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownCreateLinkWidgetTest::shouldHaveDefaultValue()
{
    MarkdownCreateLinkWidget w;

    auto mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    QVERIFY(mTitle);
    QVERIFY(mTitle->text().isEmpty());
    QVERIFY(mTitle->isClearButtonEnabled());

    auto mLink = w.findChild<QLineEdit *>(QStringLiteral("link"));
    QVERIFY(mLink);
    QVERIFY(mLink->text().isEmpty());
    QVERIFY(mLink->isClearButtonEnabled());
}

void MarkdownCreateLinkWidgetTest::shouldGenerateLink()
{
    MarkdownCreateLinkWidget w;
    auto mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    auto mLink = w.findChild<QLineEdit *>(QStringLiteral("link"));
    mLink->setText(QStringLiteral("http://www.kde.org"));
    mTitle->setText(QStringLiteral("TITLE"));
    QCOMPARE(w.linkStr(), QStringLiteral("[TITLE](http://www.kde.org)"));
}

void MarkdownCreateLinkWidgetTest::shouldEmitSignal()
{
    MarkdownCreateLinkWidget w;
    QSignalSpy spy(&w, &MarkdownCreateLinkWidget::enabledOkButton);
    auto mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    auto mLink = w.findChild<QLineEdit *>(QStringLiteral("link"));
    mTitle->setText(QStringLiteral("foo"));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), false);
    spy.clear();

    mLink->setText(QStringLiteral("dd"));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), true);
}

#include "moc_markdowncreatelinkwidgettest.cpp"

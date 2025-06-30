/*
    SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreatelinkwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mainLayout = w.findChild<QFormLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTitle = w.findChild<QLineEdit *>(u"title"_s);
    QVERIFY(mTitle);
    QVERIFY(mTitle->text().isEmpty());
    QVERIFY(mTitle->isClearButtonEnabled());

    auto mLink = w.findChild<QLineEdit *>(u"link"_s);
    QVERIFY(mLink);
    QVERIFY(mLink->text().isEmpty());
    QVERIFY(mLink->isClearButtonEnabled());
}

void MarkdownCreateLinkWidgetTest::shouldGenerateLink()
{
    MarkdownCreateLinkWidget w;
    auto mTitle = w.findChild<QLineEdit *>(u"title"_s);
    auto mLink = w.findChild<QLineEdit *>(u"link"_s);
    mLink->setText(u"http://www.kde.org"_s);
    mTitle->setText(u"TITLE"_s);
    QCOMPARE(w.linkStr(), u"[TITLE](http://www.kde.org)"_s);
}

void MarkdownCreateLinkWidgetTest::shouldEmitSignal()
{
    MarkdownCreateLinkWidget w;
    QSignalSpy spy(&w, &MarkdownCreateLinkWidget::enabledOkButton);
    auto mTitle = w.findChild<QLineEdit *>(u"title"_s);
    auto mLink = w.findChild<QLineEdit *>(u"link"_s);
    mTitle->setText(u"foo"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), false);
    spy.clear();

    mLink->setText(u"dd"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), true);
}

#include "moc_markdowncreatelinkwidgettest.cpp"

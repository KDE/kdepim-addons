/*
    SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreateimagewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "markdowncreateimagewidget.h"
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSignalSpy>
#include <QSpinBox>

#include <QTest>
QTEST_MAIN(MarkdownCreateImageWidgetTest)

MarkdownCreateImageWidgetTest::MarkdownCreateImageWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownCreateImageWidgetTest::shouldHaveDefaultValue()
{
    MarkdownCreateImageWidget w;

    auto mainLayout = w.findChild<QFormLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTitle = w.findChild<QLineEdit *>(u"title"_s);
    QVERIFY(mTitle);
    QVERIFY(mTitle->text().isEmpty());
    QVERIFY(mTitle->isClearButtonEnabled());

    auto mLink = w.findChild<QLineEdit *>(u"image"_s);
    QVERIFY(mLink);
    QVERIFY(mLink->text().isEmpty());
    QVERIFY(mLink->isClearButtonEnabled());

    auto mAlternateText = w.findChild<QLineEdit *>(u"alternatetext"_s);
    QVERIFY(mAlternateText);
    QVERIFY(mAlternateText->text().isEmpty());
    QVERIFY(mAlternateText->isClearButtonEnabled());

    auto mKeepOriginalSize = w.findChild<QCheckBox *>(u"keeporiginalsize"_s);
    QVERIFY(mKeepOriginalSize);
    QVERIFY(mKeepOriginalSize->isChecked());

    auto mLabWidth = w.findChild<QLabel *>(u"labwidth"_s);
    QVERIFY(mLabWidth);
    QVERIFY(!mLabWidth->text().isEmpty());

    auto mWidth = w.findChild<QSpinBox *>(u"mwidth"_s);
    QCOMPARE(mWidth->minimum(), 1);
    QCOMPARE(mWidth->maximum(), 999);
    QVERIFY(!mWidth->isEnabled());

    auto mLabHeight = w.findChild<QLabel *>(u"labheight"_s);
    QVERIFY(mLabHeight);
    QVERIFY(!mLabHeight->text().isEmpty());

    auto mHeight = w.findChild<QSpinBox *>(u"mheight"_s);
    QCOMPARE(mHeight->minimum(), 1);
    QCOMPARE(mHeight->maximum(), 999);
    QVERIFY(!mHeight->isEnabled());

    auto sizeWidget = w.findChild<QWidget *>(u"sizeWidget"_s);
    QVERIFY(sizeWidget);

    auto sizeWidgetLayout = w.findChild<QHBoxLayout *>(u"sizeWidgetLayout"_s);
    QVERIFY(sizeWidgetLayout);
    QCOMPARE(sizeWidgetLayout->contentsMargins(), QMargins());
}

void MarkdownCreateImageWidgetTest::shouldGenerateLink()
{
    MarkdownCreateImageWidget w;
    auto mTitle = w.findChild<QLineEdit *>(u"title"_s);
    auto mLink = w.findChild<QLineEdit *>(u"image"_s);
    auto mAlternateText = w.findChild<QLineEdit *>(u"alternatetext"_s);
    mLink->setText(u"http://www.kde.org"_s);
    mTitle->setText(u"TITLE"_s);
    QCOMPARE(w.linkStr(), u"![TITLE](http://www.kde.org)"_s);

    mAlternateText->setText(u"alternate"_s);
    QCOMPARE(w.linkStr(), u"![TITLE](http://www.kde.org \"alternate\"_s");
}

void MarkdownCreateImageWidgetTest::shouldChangeState()
{
    MarkdownCreateImageWidget w;
    auto mKeepOriginalSize = w.findChild<QCheckBox *>(u"keeporiginalsize"_s);
    auto mLabWidth = w.findChild<QLabel *>(u"labwidth"_s);
    auto mWidth = w.findChild<QSpinBox *>(u"mwidth"_s);
    auto mLabHeight = w.findChild<QLabel *>(u"labheight"_s);
    auto mHeight = w.findChild<QSpinBox *>(u"mheight"_s);

    mKeepOriginalSize->setChecked(true);
    QVERIFY(!mLabWidth->isEnabled());
    QVERIFY(!mWidth->isEnabled());
    QVERIFY(!mLabHeight->isEnabled());
    QVERIFY(!mHeight->isEnabled());

    mKeepOriginalSize->setChecked(false);
    QVERIFY(mLabWidth->isEnabled());
    QVERIFY(mWidth->isEnabled());
    QVERIFY(mLabHeight->isEnabled());
    QVERIFY(mHeight->isEnabled());
}

void MarkdownCreateImageWidgetTest::shouldAddSize()
{
    MarkdownCreateImageWidget w;
    auto mTitle = w.findChild<QLineEdit *>(u"title"_s);
    auto mLink = w.findChild<QLineEdit *>(u"image"_s);
    auto mAlternateText = w.findChild<QLineEdit *>(u"alternatetext"_s);
    mLink->setText(u"http://www.kde.org"_s);
    mTitle->setText(u"TITLE"_s);

    mAlternateText->setText(u"alternate"_s);
    auto mKeepOriginalSize = w.findChild<QCheckBox *>(u"keeporiginalsize"_s);
    auto mWidth = w.findChild<QSpinBox *>(u"mwidth"_s);
    auto mHeight = w.findChild<QSpinBox *>(u"mheight"_s);
    mKeepOriginalSize->setChecked(false);
    mWidth->setValue(45);
    mHeight->setValue(70);

    QCOMPARE(w.linkStr(), u"![TITLE](http://www.kde.org =45x70 \"alternate\"_s");
    mAlternateText->setText(QString());
    QCOMPARE(w.linkStr(), u"![TITLE](http://www.kde.org =45x70)"_s);
}

void MarkdownCreateImageWidgetTest::shouldEmitSignal()
{
    MarkdownCreateImageWidget w;
    QSignalSpy spy(&w, &MarkdownCreateImageWidget::enabledOkButton);
    auto mTitle = w.findChild<QLineEdit *>(u"title"_s);
    auto mLink = w.findChild<QLineEdit *>(u"image"_s);
    auto mAlternateText = w.findChild<QLineEdit *>(u"alternatetext"_s);
    mTitle->setText(u"foo"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), false);
    spy.clear();

    mAlternateText->setText(u"dd"_s);
    QCOMPARE(spy.count(), 0);
    spy.clear();

    mLink->setText(u"dd"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), true);
    spy.clear();
    mTitle->clear();
    QCOMPARE(spy.at(0).at(0).value<bool>(), false);
    spy.clear();
}

#include "moc_markdowncreateimagewidgettest.cpp"

/*
    SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreateimagewidgettest.h"
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

    auto mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    QVERIFY(mTitle);
    QVERIFY(mTitle->text().isEmpty());
    QVERIFY(mTitle->isClearButtonEnabled());

    auto mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    QVERIFY(mLink);
    QVERIFY(mLink->text().isEmpty());
    QVERIFY(mLink->isClearButtonEnabled());

    auto mAlternateText = w.findChild<QLineEdit *>(QStringLiteral("alternatetext"));
    QVERIFY(mAlternateText);
    QVERIFY(mAlternateText->text().isEmpty());
    QVERIFY(mAlternateText->isClearButtonEnabled());

    auto mKeepOriginalSize = w.findChild<QCheckBox *>(QStringLiteral("keeporiginalsize"));
    QVERIFY(mKeepOriginalSize);
    QVERIFY(mKeepOriginalSize->isChecked());

    auto mLabWidth = w.findChild<QLabel *>(QStringLiteral("labwidth"));
    QVERIFY(mLabWidth);
    QVERIFY(!mLabWidth->text().isEmpty());

    auto mWidth = w.findChild<QSpinBox *>(QStringLiteral("mwidth"));
    QCOMPARE(mWidth->minimum(), 1);
    QCOMPARE(mWidth->maximum(), 999);
    QVERIFY(!mWidth->isEnabled());

    auto mLabHeight = w.findChild<QLabel *>(QStringLiteral("labheight"));
    QVERIFY(mLabHeight);
    QVERIFY(!mLabHeight->text().isEmpty());

    auto mHeight = w.findChild<QSpinBox *>(QStringLiteral("mheight"));
    QCOMPARE(mHeight->minimum(), 1);
    QCOMPARE(mHeight->maximum(), 999);
    QVERIFY(!mHeight->isEnabled());

    auto sizeWidget = w.findChild<QWidget *>(QStringLiteral("sizeWidget"));
    QVERIFY(sizeWidget);

    auto sizeWidgetLayout = w.findChild<QHBoxLayout *>(QStringLiteral("sizeWidgetLayout"));
    QVERIFY(sizeWidgetLayout);
    QCOMPARE(sizeWidgetLayout->contentsMargins(), QMargins());
}

void MarkdownCreateImageWidgetTest::shouldGenerateLink()
{
    MarkdownCreateImageWidget w;
    auto mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    auto mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    auto mAlternateText = w.findChild<QLineEdit *>(QStringLiteral("alternatetext"));
    mLink->setText(QStringLiteral("http://www.kde.org"));
    mTitle->setText(QStringLiteral("TITLE"));
    QCOMPARE(w.linkStr(), QStringLiteral("![TITLE](http://www.kde.org)"));

    mAlternateText->setText(QStringLiteral("alternate"));
    QCOMPARE(w.linkStr(), QStringLiteral("![TITLE](http://www.kde.org \"alternate\")"));
}

void MarkdownCreateImageWidgetTest::shouldChangeState()
{
    MarkdownCreateImageWidget w;
    auto mKeepOriginalSize = w.findChild<QCheckBox *>(QStringLiteral("keeporiginalsize"));
    auto mLabWidth = w.findChild<QLabel *>(QStringLiteral("labwidth"));
    auto mWidth = w.findChild<QSpinBox *>(QStringLiteral("mwidth"));
    auto mLabHeight = w.findChild<QLabel *>(QStringLiteral("labheight"));
    auto mHeight = w.findChild<QSpinBox *>(QStringLiteral("mheight"));

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
    auto mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    auto mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    auto mAlternateText = w.findChild<QLineEdit *>(QStringLiteral("alternatetext"));
    mLink->setText(QStringLiteral("http://www.kde.org"));
    mTitle->setText(QStringLiteral("TITLE"));

    mAlternateText->setText(QStringLiteral("alternate"));
    auto mKeepOriginalSize = w.findChild<QCheckBox *>(QStringLiteral("keeporiginalsize"));
    auto mWidth = w.findChild<QSpinBox *>(QStringLiteral("mwidth"));
    auto mHeight = w.findChild<QSpinBox *>(QStringLiteral("mheight"));
    mKeepOriginalSize->setChecked(false);
    mWidth->setValue(45);
    mHeight->setValue(70);

    QCOMPARE(w.linkStr(), QStringLiteral("![TITLE](http://www.kde.org =45x70 \"alternate\")"));
    mAlternateText->setText(QString());
    QCOMPARE(w.linkStr(), QStringLiteral("![TITLE](http://www.kde.org =45x70)"));
}

void MarkdownCreateImageWidgetTest::shouldEmitSignal()
{
    MarkdownCreateImageWidget w;
    QSignalSpy spy(&w, &MarkdownCreateImageWidget::enabledOkButton);
    auto mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    auto mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    auto mAlternateText = w.findChild<QLineEdit *>(QStringLiteral("alternatetext"));
    mTitle->setText(QStringLiteral("foo"));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), false);
    spy.clear();

    mAlternateText->setText(QStringLiteral("dd"));
    QCOMPARE(spy.count(), 0);
    spy.clear();

    mLink->setText(QStringLiteral("dd"));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<bool>(), true);
    spy.clear();
    mTitle->clear();
    QCOMPARE(spy.at(0).at(0).value<bool>(), false);
    spy.clear();
}

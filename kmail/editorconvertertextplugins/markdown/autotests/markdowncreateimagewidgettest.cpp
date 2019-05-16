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
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QSignalSpy>

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
    QVERIFY(mTitle->isClearButtonEnabled());

    QLineEdit *mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    QVERIFY(mLink);
    QVERIFY(mLink->text().isEmpty());
    QVERIFY(mLink->isClearButtonEnabled());

    QLineEdit *mAlternateText = w.findChild<QLineEdit *>(QStringLiteral("alternatetext"));
    QVERIFY(mAlternateText);
    QVERIFY(mAlternateText->text().isEmpty());
    QVERIFY(mAlternateText->isClearButtonEnabled());

    QCheckBox *mKeepOriginalSize = w.findChild<QCheckBox *>(QStringLiteral("keeporiginalsize"));
    QVERIFY(mKeepOriginalSize);
    QVERIFY(mKeepOriginalSize->isChecked());

    QLabel *mLabWidth = w.findChild<QLabel *>(QStringLiteral("labwidth"));
    QVERIFY(mLabWidth);
    QVERIFY(!mLabWidth->text().isEmpty());

    QSpinBox *mWidth = w.findChild<QSpinBox *>(QStringLiteral("mwidth"));
    QCOMPARE(mWidth->minimum(), 1);
    QCOMPARE(mWidth->maximum(), 999);
    QVERIFY(!mWidth->isEnabled());

    QLabel *mLabHeight = w.findChild<QLabel *>(QStringLiteral("labheight"));
    QVERIFY(mLabHeight);
    QVERIFY(!mLabHeight->text().isEmpty());

    QSpinBox *mHeight = w.findChild<QSpinBox *>(QStringLiteral("mheight"));
    QCOMPARE(mHeight->minimum(), 1);
    QCOMPARE(mHeight->maximum(), 999);
    QVERIFY(!mHeight->isEnabled());
}

void MarkdownCreateImageWidgetTest::shouldGenerateLink()
{
    MarkdownCreateImageWidget w;
    QLineEdit *mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    QLineEdit *mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    QLineEdit *mAlternateText = w.findChild<QLineEdit *>(QStringLiteral("alternatetext"));
    mLink->setText(QStringLiteral("http://www.kde.org"));
    mTitle->setText(QStringLiteral("TITLE"));
    QCOMPARE(w.linkStr(), QStringLiteral("![TITLE](http://www.kde.org)"));

    mAlternateText->setText(QStringLiteral("alternate"));
    QCOMPARE(w.linkStr(), QStringLiteral("![TITLE](http://www.kde.org \"alternate\")"));
}

void MarkdownCreateImageWidgetTest::shouldChangeState()
{
    MarkdownCreateImageWidget w;
    QCheckBox *mKeepOriginalSize = w.findChild<QCheckBox *>(QStringLiteral("keeporiginalsize"));
    QLabel *mLabWidth = w.findChild<QLabel *>(QStringLiteral("labwidth"));
    QSpinBox *mWidth = w.findChild<QSpinBox *>(QStringLiteral("mwidth"));
    QLabel *mLabHeight = w.findChild<QLabel *>(QStringLiteral("labheight"));
    QSpinBox *mHeight = w.findChild<QSpinBox *>(QStringLiteral("mheight"));

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
    QLineEdit *mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    QLineEdit *mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    QLineEdit *mAlternateText = w.findChild<QLineEdit *>(QStringLiteral("alternatetext"));
    mLink->setText(QStringLiteral("http://www.kde.org"));
    mTitle->setText(QStringLiteral("TITLE"));

    mAlternateText->setText(QStringLiteral("alternate"));
    QCheckBox *mKeepOriginalSize = w.findChild<QCheckBox *>(QStringLiteral("keeporiginalsize"));
    QSpinBox *mWidth = w.findChild<QSpinBox *>(QStringLiteral("mwidth"));
    QSpinBox *mHeight = w.findChild<QSpinBox *>(QStringLiteral("mheight"));
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
    QLineEdit *mTitle = w.findChild<QLineEdit *>(QStringLiteral("title"));
    QLineEdit *mLink = w.findChild<QLineEdit *>(QStringLiteral("image"));
    QLineEdit *mAlternateText = w.findChild<QLineEdit *>(QStringLiteral("alternatetext"));
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

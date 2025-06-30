/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmbeforedeletingmessageboxwidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(ConfirmBeforeDeletingMessageBoxWidgetTest)
ConfirmBeforeDeletingMessageBoxWidgetTest::ConfirmBeforeDeletingMessageBoxWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingMessageBoxWidgetTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingMessageBoxWidget w;
    auto mUseSameResultForOtherCheck = w.findChild<QCheckBox *>(u"mUseSameResultForOtherCheck"_s);
    QVERIFY(mUseSameResultForOtherCheck);
    QVERIFY(!mUseSameResultForOtherCheck->text().isEmpty());
    QVERIFY(!mUseSameResultForOtherCheck->isChecked());

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto textLayout = w.findChild<QVBoxLayout *>(u"textLayout"_s);
    QVERIFY(textLayout);
    QCOMPARE(textLayout->contentsMargins(), QMargins{});

    auto iconLabel = w.findChild<QLabel *>(u"iconLabel"_s);
    QVERIFY(iconLabel);
    QVERIFY(iconLabel->text().isEmpty());

    auto mLabelInfo = w.findChild<QLabel *>(u"mLabelInfo"_s);
    QVERIFY(mLabelInfo);
    QVERIFY(mLabelInfo->text().isEmpty());
    QVERIFY(mLabelInfo->wordWrap());
}

#include "moc_confirmbeforedeletingmessageboxwidgettest.cpp"

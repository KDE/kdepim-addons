/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlconfigurewidgettest.h"
#include "../insertshorturlconfigurewidget.h"

#include <QComboBox>
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(InsertShorturlConfigureWidgetTest)

InsertShorturlConfigureWidgetTest::InsertShorturlConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void InsertShorturlConfigureWidgetTest::shouldHaveDefaultValues()
{
    InsertShorturlConfigureWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    auto mShortUrlServer = w.findChild<QComboBox *>(QStringLiteral("shorturlserver"));
    QVERIFY(mShortUrlServer);
}

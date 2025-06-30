/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto lab = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    auto mShortUrlServer = w.findChild<QComboBox *>(u"shorturlserver"_s);
    QVERIFY(mShortUrlServer);
}

#include "moc_insertshorturlconfigurewidgettest.cpp"

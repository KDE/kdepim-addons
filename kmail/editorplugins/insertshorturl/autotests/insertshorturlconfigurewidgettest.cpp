/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlconfigurewidgettest.h"

#include "../insertshorturlconfigurewidget.h"

#include <QComboBox>
#include <QLabel>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(InsertShorturlConfigureWidgetTest)

InsertShorturlConfigureWidgetTest::InsertShorturlConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void InsertShorturlConfigureWidgetTest::shouldHaveDefaultValues()
{
    InsertShorturlConfigureWidget w;

    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto lab = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    const auto mShortUrlServer = w.findChild<QComboBox *>(u"shorturlserver"_s);
    QVERIFY(mShortUrlServer);
}

#include "moc_insertshorturlconfigurewidgettest.cpp"

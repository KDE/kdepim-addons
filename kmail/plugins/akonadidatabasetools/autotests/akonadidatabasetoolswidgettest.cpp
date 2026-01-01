/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "akonadidatabasetoolswidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "akonadidatabasetoolswidget.h"
#include <QPlainTextEdit>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(AkonadiDatabaseToolsWidgetTest)
AkonadiDatabaseToolsWidgetTest::AkonadiDatabaseToolsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AkonadiDatabaseToolsWidgetTest::shouldHaveDefaultValues()
{
    AkonadiDatabaseToolsWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mPlainTextEdit = w.findChild<QPlainTextEdit *>(u"mPlainTextEdit"_s);
    QVERIFY(mPlainTextEdit);
    QVERIFY(mPlainTextEdit->toPlainText().isEmpty());
    QVERIFY(mPlainTextEdit->isReadOnly());
}

#include "moc_akonadidatabasetoolswidgettest.cpp"

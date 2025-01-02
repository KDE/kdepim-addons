/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "akonadidatabasetoolswidgettest.h"
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
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mPlainTextEdit = w.findChild<QPlainTextEdit *>(QStringLiteral("mPlainTextEdit"));
    QVERIFY(mPlainTextEdit);
    QVERIFY(mPlainTextEdit->toPlainText().isEmpty());
    QVERIFY(mPlainTextEdit->isReadOnly());
}

#include "moc_akonadidatabasetoolswidgettest.cpp"

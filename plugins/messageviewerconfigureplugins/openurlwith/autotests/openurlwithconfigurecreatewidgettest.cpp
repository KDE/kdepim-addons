/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatewidgettest.h"
#include "openurlwithconfigurecreatewidget.h"
#include <QLineEdit>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OpenUrlWithConfigureCreateWidgetTest)
OpenUrlWithConfigureCreateWidgetTest::OpenUrlWithConfigureCreateWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureCreateWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureCreateWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mServerName = w.findChild<QLineEdit *>(QStringLiteral("mServerName"));
    QVERIFY(mServerName);
    QVERIFY(mServerName->text().isEmpty());

    auto mCommand = w.findChild<QLineEdit *>(QStringLiteral("mCommand"));
    QVERIFY(mCommand);
    QVERIFY(mCommand->text().isEmpty());
}

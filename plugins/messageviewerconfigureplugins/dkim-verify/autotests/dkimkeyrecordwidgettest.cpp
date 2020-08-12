/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimkeyrecordwidgettest.h"
#include "dkimkeyrecordwidget.h"
#include <MessageViewer/DKIMManagerKeyWidget>
#include <QHBoxLayout>
#include <QTest>
QTEST_MAIN(DKIMKeyRecordWidgetTest)

DKIMKeyRecordWidgetTest::DKIMKeyRecordWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMKeyRecordWidgetTest::shouldHaveDefaultValues()
{
    DKIMKeyRecordWidget w;
    QHBoxLayout *mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    MessageViewer::DKIMManagerKeyWidget *mManagerKeyWidget = w.findChild<MessageViewer::DKIMManagerKeyWidget *>(QStringLiteral("mManagerKeyWidget"));
    QVERIFY(mManagerKeyWidget);
}

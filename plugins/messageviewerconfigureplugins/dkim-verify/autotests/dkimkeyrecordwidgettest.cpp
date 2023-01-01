/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

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
    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mManagerKeyWidget = w.findChild<MessageViewer::DKIMManagerKeyWidget *>(QStringLiteral("mManagerKeyWidget"));
    QVERIFY(mManagerKeyWidget);
}

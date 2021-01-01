/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectinformationwidgettest.h"
#include "widgets/mergecontactselectinformationwidget.h"
#include "widgets/mergecontactselectlistwidget.h"
#include <QTest>
#include <QLayout>
MergeContactSelectInformationWidgetTest::MergeContactSelectInformationWidgetTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectInformationWidgetTest::~MergeContactSelectInformationWidgetTest()
{
}

void MergeContactSelectInformationWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectInformationWidget w;
    QCOMPARE(w.layout()->count(), 0);
}

QTEST_MAIN(MergeContactSelectInformationWidgetTest)

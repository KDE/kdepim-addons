/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectinformationwidgettest.h"
#include "widgets/mergecontactselectinformationwidget.h"
#include "widgets/mergecontactselectlistwidget.h"
#include <QLayout>
#include <QTest>
MergeContactSelectInformationWidgetTest::MergeContactSelectInformationWidgetTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectInformationWidgetTest::~MergeContactSelectInformationWidgetTest() = default;

void MergeContactSelectInformationWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectInformationWidget w;
    QCOMPARE(w.layout()->count(), 0);
}

QTEST_MAIN(MergeContactSelectInformationWidgetTest)

#include "moc_mergecontactselectinformationwidgettest.cpp"

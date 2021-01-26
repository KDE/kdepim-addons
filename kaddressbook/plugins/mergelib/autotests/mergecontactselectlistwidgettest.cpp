/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectlistwidgettest.h"
#include "job/mergecontacts.h"
#include "widgets/mergecontactselectlistwidget.h"
#include <QLabel>
#include <QListWidget>
#include <QTest>

MergeContactSelectListWidgetTest::MergeContactSelectListWidgetTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectListWidgetTest::~MergeContactSelectListWidgetTest()
{
}

void MergeContactSelectListWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectListWidget selectListWidget;

    QLabel *title = selectListWidget.findChild<QLabel *>(QStringLiteral("title"));
    QVERIFY(title);
    QListWidget *listWidget = selectListWidget.findChild<QListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(listWidget);
    QCOMPARE(selectListWidget.selectedContact(), -1);
    QCOMPARE(selectListWidget.conflictType(), KABMergeContacts::MergeContacts::None);
}

QTEST_MAIN(MergeContactSelectListWidgetTest)

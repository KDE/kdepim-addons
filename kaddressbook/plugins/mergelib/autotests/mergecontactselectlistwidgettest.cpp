/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

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

MergeContactSelectListWidgetTest::~MergeContactSelectListWidgetTest() = default;

void MergeContactSelectListWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectListWidget selectListWidget;

    auto title = selectListWidget.findChild<QLabel *>(QStringLiteral("title"));
    QVERIFY(title);
    auto listWidget = selectListWidget.findChild<QListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(listWidget);
    QCOMPARE(selectListWidget.selectedContact(), -1);
    QCOMPARE(selectListWidget.conflictType(), KABMergeContacts::MergeContacts::None);
}

QTEST_MAIN(MergeContactSelectListWidgetTest)

#include "moc_mergecontactselectlistwidgettest.cpp"

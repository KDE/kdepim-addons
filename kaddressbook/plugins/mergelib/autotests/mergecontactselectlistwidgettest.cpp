/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

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

    const auto title = selectListWidget.findChild<QLabel *>(QStringLiteral("title"));
    QVERIFY(title);
    const auto listWidget = selectListWidget.findChild<QListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(listWidget);
    QCOMPARE(selectListWidget.selectedContact(), -1);
    QCOMPARE((int)selectListWidget.conflictType(), (int)KABMergeContacts::MergeContacts::None);
}

QTEST_MAIN(MergeContactSelectListWidgetTest)

#include "moc_mergecontactselectlistwidgettest.cpp"

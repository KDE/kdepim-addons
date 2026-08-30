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
using namespace Qt::Literals::StringLiterals;

MergeContactSelectListWidgetTest::MergeContactSelectListWidgetTest(QObject *parent)
    : QObject(parent)
{
}

MergeContactSelectListWidgetTest::~MergeContactSelectListWidgetTest() = default;

void MergeContactSelectListWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectListWidget selectListWidget;

    const auto title = selectListWidget.findChild<QLabel *>(u"title"_s);
    QVERIFY(title);
    const auto listWidget = selectListWidget.findChild<QListWidget *>(u"listwidget"_s);
    QVERIFY(listWidget);
    QCOMPARE(selectListWidget.selectedContact(), -1);
    QCOMPARE((int)selectListWidget.conflictType(), (int)KABMergeContacts::MergeContacts::None);
}

QTEST_MAIN(MergeContactSelectListWidgetTest)

#include "moc_mergecontactselectlistwidgettest.cpp"

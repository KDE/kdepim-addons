/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderwidgettest.h"
#include "../selectimapfolderwidget.h"
#include <QLineEdit>
#include <QTest>
#include <QToolButton>
#include <QTreeView>
#include <QVBoxLayout>

SelectImapFolderWidgetTest::SelectImapFolderWidgetTest(QObject *parent)
    : QObject(parent)
{
}

SelectImapFolderWidgetTest::~SelectImapFolderWidgetTest() = default;

void SelectImapFolderWidgetTest::shouldHaveDefaultValue()
{
    KSieveUi::SieveImapAccountSettings account;
    SelectImapFolderWidget w(account);
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTreeView = w.findChild<QTreeView *>(QStringLiteral("treeview"));
    QVERIFY(mTreeView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>(QStringLiteral("searchline"));
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchLineEdit->text().isEmpty());

    auto refreshImap = w.findChild<QToolButton *>(QStringLiteral("refreshimap"));
    QVERIFY(refreshImap);
    QVERIFY(!refreshImap->toolTip().isEmpty());
}

QTEST_MAIN(SelectImapFolderWidgetTest)

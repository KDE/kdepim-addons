/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderwidgettest.h"
#include "../selectimapfolderwidget.h"
#include <QTreeView>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTest>
#include <QToolButton>

SelectImapFolderWidgetTest::SelectImapFolderWidgetTest(QObject *parent)
    : QObject(parent)
{
}

SelectImapFolderWidgetTest::~SelectImapFolderWidgetTest()
{
}

void SelectImapFolderWidgetTest::shouldHaveDefaultValue()
{
    KSieveUi::SieveImapAccountSettings account;
    SelectImapFolderWidget w(account);
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QTreeView *mTreeView = w.findChild<QTreeView *>(QStringLiteral("treeview"));
    QVERIFY(mTreeView);

    QLineEdit *mSearchLineEdit = w.findChild<QLineEdit *>(QStringLiteral("searchline"));
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchLineEdit->text().isEmpty());

    QToolButton *refreshImap = w.findChild<QToolButton *>(QStringLiteral("refreshimap"));
    QVERIFY(refreshImap);
    QVERIFY(!refreshImap->toolTip().isEmpty());
}

QTEST_MAIN(SelectImapFolderWidgetTest)

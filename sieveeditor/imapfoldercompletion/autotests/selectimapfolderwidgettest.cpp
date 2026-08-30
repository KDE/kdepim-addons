/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderwidgettest.h"
#include "../selectimapfolderwidget.h"
#include <QLineEdit>
#include <QTest>
#include <QToolButton>
#include <QTreeView>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

SelectImapFolderWidgetTest::SelectImapFolderWidgetTest(QObject *parent)
    : QObject(parent)
{
}

SelectImapFolderWidgetTest::~SelectImapFolderWidgetTest() = default;

void SelectImapFolderWidgetTest::shouldHaveDefaultValue()
{
    KSieveCore::SieveImapAccountSettings account;
    SelectImapFolderWidget w(account);
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mTreeView = w.findChild<QTreeView *>(u"treeview"_s);
    QVERIFY(mTreeView);

    const auto mSearchLineEdit = w.findChild<QLineEdit *>(u"searchline"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchLineEdit->text().isEmpty());

    const auto refreshImap = w.findChild<QToolButton *>(u"refreshimap"_s);
    QVERIFY(refreshImap);
    QVERIFY(!refreshImap->toolTip().isEmpty());
}

QTEST_MAIN(SelectImapFolderWidgetTest)

#include "moc_selectimapfolderwidgettest.cpp"

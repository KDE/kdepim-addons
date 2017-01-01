/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "selectimapfolderdialogtest.h"
#include "../selectimapfolderdialog.h"
#include "../selectimapfolderwidget.h"
#include <QTest>
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <KSieveUi/SieveImapAccountSettings>

SelectImapFolderDialogTest::SelectImapFolderDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

SelectImapFolderDialogTest::~SelectImapFolderDialogTest()
{

}

void SelectImapFolderDialogTest::shouldHaveDefaultValue()
{
    KSieveUi::SieveImapAccountSettings account;
    SelectImapFolderDialog w(account);

    SelectImapFolderWidget *mSelectImapFolderWidget = w.findChild<SelectImapFolderWidget *>(QStringLiteral("selectimapfolderwidget"));
    QVERIFY(mSelectImapFolderWidget);

    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QVERIFY(!w.windowTitle().isEmpty());
}

QTEST_MAIN(SelectImapFolderDialogTest)

/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderdialogtest.h"
#include "../selectimapfolderdialog.h"
#include "../selectimapfolderwidget.h"
#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>

SelectImapFolderDialogTest::SelectImapFolderDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

SelectImapFolderDialogTest::~SelectImapFolderDialogTest() = default;

void SelectImapFolderDialogTest::shouldHaveDefaultValue()
{
    KSieveUi::SieveImapAccountSettings account;
    SelectImapFolderDialog w(account);

    auto mSelectImapFolderWidget = w.findChild<SelectImapFolderWidget *>(QStringLiteral("selectimapfolderwidget"));
    QVERIFY(mSelectImapFolderWidget);

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    const QList<QAbstractButton *> lst = buttonBox->buttons();
    bool foundCreateFolderButton = false;
    for (QAbstractButton *b : lst) {
        if (b->objectName() == QLatin1String("createfolder")) {
            foundCreateFolderButton = true;
            QVERIFY(!b->isEnabled());
            break;
        }
    }
    QVERIFY(foundCreateFolderButton);

    QVERIFY(!w.windowTitle().isEmpty());
}

QTEST_MAIN(SelectImapFolderDialogTest)

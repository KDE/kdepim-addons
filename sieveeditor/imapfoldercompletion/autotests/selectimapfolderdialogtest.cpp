/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderdialogtest.h"
#include "../selectimapfolderdialog.h"
#include "../selectimapfolderwidget.h"
#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

SelectImapFolderDialogTest::SelectImapFolderDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

SelectImapFolderDialogTest::~SelectImapFolderDialogTest() = default;

void SelectImapFolderDialogTest::shouldHaveDefaultValue()
{
    KSieveCore::SieveImapAccountSettings account;
    SelectImapFolderDialog w(account);

    const auto mSelectImapFolderWidget = w.findChild<SelectImapFolderWidget *>(u"selectimapfolderwidget"_s);
    QVERIFY(mSelectImapFolderWidget);

    const auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    const QList<QAbstractButton *> lst = buttonBox->buttons();
    bool foundCreateFolderButton = false;
    for (QAbstractButton *b : lst) {
        if (b->objectName() == "createfolder"_L1) {
            foundCreateFolderButton = true;
            QVERIFY(!b->isEnabled());
            break;
        }
    }
    QVERIFY(foundCreateFolderButton);

    QVERIFY(!w.windowTitle().isEmpty());
}

QTEST_MAIN(SelectImapFolderDialogTest)

#include "moc_selectimapfolderdialogtest.cpp"

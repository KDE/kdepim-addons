/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfoldermodeltest.h"
#include "../selectimapfoldermodel.h"
#include <KSieveUi/SieveImapAccountSettings>
#include <QTest>

SelectImapFolderModelTest::SelectImapFolderModelTest(QObject *parent)
    : QObject(parent)
{
}

SelectImapFolderModelTest::~SelectImapFolderModelTest()
{
}

void SelectImapFolderModelTest::shouldNotCreateModelIfAccountIsNotValid()
{
    SelectImapFolderModel model;
    KSieveUi::SieveImapAccountSettings account;
    QVERIFY(!account.isValid());
    bool modelIsInitialized = false;
    QVERIFY(!model.folderModel(account, modelIsInitialized));
    QVERIFY(!modelIsInitialized);
}

QTEST_MAIN(SelectImapFolderModelTest)

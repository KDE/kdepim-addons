/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfoldermodeltest.h"
#include "../selectimapfoldermodel.h"
#include <KSieveCore/SieveImapAccountSettings>
#include <QTest>

SelectImapFolderModelTest::SelectImapFolderModelTest(QObject *parent)
    : QObject(parent)
{
}

SelectImapFolderModelTest::~SelectImapFolderModelTest() = default;

void SelectImapFolderModelTest::shouldNotCreateModelIfAccountIsNotValid()
{
    SelectImapFolderModel model;
    KSieveCore::SieveImapAccountSettings account;
    QVERIFY(!account.isValid());
    bool modelIsInitialized = false;
    QVERIFY(!model.folderModel(account, modelIsInitialized));
    QVERIFY(!modelIsInitialized);
}

QTEST_MAIN(SelectImapFolderModelTest)

#include "moc_selectimapfoldermodeltest.cpp"

/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockblockableitemsdialogtest.h"
#include "../lib/widgets/adblockblockableitemsdialog.h"
#include "../lib/widgets/adblockblockableitemswidget.h"

#include <QDialogButtonBox>
#include <QTest>
using namespace AdBlock;
AdBlockBlockableItemsDialogTest::AdBlockBlockableItemsDialogTest(QObject *parent)
    : QObject(parent)
{
}

AdBlockBlockableItemsDialogTest::~AdBlockBlockableItemsDialogTest()
{
}

void AdBlockBlockableItemsDialogTest::shouldHaveDefaultValue()
{
    AdBlockBlockableItemsDialog w;
    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    AdBlockBlockableItemsWidget *mBlockableItems = w.findChild<AdBlockBlockableItemsWidget *>(QStringLiteral("blockableitemswidget"));
    QVERIFY(mBlockableItems);
}

QTEST_MAIN(AdBlockBlockableItemsDialogTest)

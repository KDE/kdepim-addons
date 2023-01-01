/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

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

AdBlockBlockableItemsDialogTest::~AdBlockBlockableItemsDialogTest() = default;

void AdBlockBlockableItemsDialogTest::shouldHaveDefaultValue()
{
    AdBlockBlockableItemsDialog w;
    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    auto mBlockableItems = w.findChild<AdBlockBlockableItemsWidget *>(QStringLiteral("blockableitemswidget"));
    QVERIFY(mBlockableItems);
}

QTEST_MAIN(AdBlockBlockableItemsDialogTest)

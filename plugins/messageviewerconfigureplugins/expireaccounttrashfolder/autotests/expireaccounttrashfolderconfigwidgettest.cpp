/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "expireaccounttrashfolderconfigwidgettest.h"
#include "../expireaccounttrashfolderconfigwidget.h"
#include <QTest>
QTEST_MAIN(ExpireAccountTrashFolderConfigWidgetTest)
ExpireAccountTrashFolderConfigWidgetTest::ExpireAccountTrashFolderConfigWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void ExpireAccountTrashFolderConfigWidgetTest::shouldHaveDefaultValues()
{
    ExpireAccountTrashFolderConfigWidget w;
}

#include "moc_expireaccounttrashfolderconfigwidgettest.cpp"

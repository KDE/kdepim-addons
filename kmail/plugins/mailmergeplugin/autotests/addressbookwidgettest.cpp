/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "addressbookwidgettest.h"
#include <QTest>
AddressBookWidgetTest::AddressBookWidgetTest(QObject *parent)
    : QObject(parent)
{
}

AddressBookWidgetTest::~AddressBookWidgetTest() = default;

QTEST_MAIN(AddressBookWidgetTest)

#include "moc_addressbookwidgettest.cpp"

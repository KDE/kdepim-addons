/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef ADDRESSBOOKWIDGETTEST_H
#define ADDRESSBOOKWIDGETTEST_H

#include <QObject>

class AddressBookWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AddressBookWidgetTest(QObject *parent = nullptr);
    ~AddressBookWidgetTest();
};

#endif // ADDRESSBOOKWIDGETTEST_H

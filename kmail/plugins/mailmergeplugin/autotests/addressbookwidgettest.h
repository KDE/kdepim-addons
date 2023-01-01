/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class AddressBookWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AddressBookWidgetTest(QObject *parent = nullptr);
    ~AddressBookWidgetTest() override;
};

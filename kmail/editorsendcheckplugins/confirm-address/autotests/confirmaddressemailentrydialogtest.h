/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef CONFIRMADDRESSEMAILENTRYDIALOGTEST_H
#define CONFIRMADDRESSEMAILENTRYDIALOGTEST_H

#include <QObject>

class ConfirmAddressEmailEntryDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressEmailEntryDialogTest(QObject *parent = nullptr);
    ~ConfirmAddressEmailEntryDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CONFIRMADDRESSEMAILENTRYDIALOGTEST_H

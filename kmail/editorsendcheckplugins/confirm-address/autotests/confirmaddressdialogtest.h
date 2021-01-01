/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSDIALOGTEST_H
#define CONFIRMADDRESSDIALOGTEST_H

#include <QObject>

class ConfirmAddressDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressDialogTest(QObject *parent = nullptr);
    ~ConfirmAddressDialogTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CONFIRMADDRESSDIALOGTEST_H

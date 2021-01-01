/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSWIDGETTEST_H
#define CONFIRMADDRESSWIDGETTEST_H

#include <QObject>

class ConfirmAddressWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressWidgetTest(QObject *parent = nullptr);
    ~ConfirmAddressWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddAddress();
    void shouldAddValidAndInvalidAddresses();
    void shouldHaveCheckableItem();
    void shouldGetWhileListEmails();
};

#endif // CONFIRMADDRESSWIDGETTEST_H

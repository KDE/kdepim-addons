/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSCONFIGURETABTEST_H
#define CONFIRMADDRESSCONFIGURETABTEST_H

#include <QObject>

class ConfirmAddressConfigureTabTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureTabTest(QObject *parent = nullptr);
    ~ConfirmAddressConfigureTabTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CONFIRMADDRESSCONFIGURETABTEST_H

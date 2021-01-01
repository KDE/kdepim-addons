/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSPLUGINTEST_H
#define CONFIRMADDRESSPLUGINTEST_H

#include <QObject>

class ConfirmAddressPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressPluginTest(QObject *parent = nullptr);
    ~ConfirmAddressPluginTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CONFIRMADDRESSPLUGINTEST_H

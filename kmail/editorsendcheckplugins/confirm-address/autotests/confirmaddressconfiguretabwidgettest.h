/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSCONFIGURETABWIDGETTEST_H
#define CONFIRMADDRESSCONFIGURETABWIDGETTEST_H

#include <QObject>

class ConfirmAddressConfigureTabWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureTabWidgetTest(QObject *parent = nullptr);
    ~ConfirmAddressConfigureTabWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CONFIRMADDRESSCONFIGURETABWIDGETTEST_H

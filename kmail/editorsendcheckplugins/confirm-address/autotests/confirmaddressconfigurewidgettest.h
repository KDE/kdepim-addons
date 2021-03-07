/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSCONFIGUREWIDGETTEST_H
#define CONFIRMADDRESSCONFIGUREWIDGETTEST_H

#include <QObject>

class ConfirmAddressConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureWidgetTest(QObject *parent = nullptr);
    ~ConfirmAddressConfigureWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldLoadSaveResetValue();
};

#endif // CONFIRMADDRESSCONFIGUREWIDGETTEST_H

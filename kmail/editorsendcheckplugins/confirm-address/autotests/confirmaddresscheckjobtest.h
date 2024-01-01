/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfirmAddressCheckJobTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressCheckJobTest(QObject *parent = nullptr);
    ~ConfirmAddressCheckJobTest() override;
private Q_SLOTS:
    void shouldHaveEmptyResultByDefault();
    void shouldReturnEmptyResultWhenNoAddress();
    void shouldReturnAllValidEmailsDomain();
    void shouldReturnAllInValidEmailsDomain();
    void shouldReturnValidAndInvalid();
    void shouldNotDuplicateValue();
    void shouldReturnAllValidEmailsDomainRejectedDomain();
    void shouldReturnAllInValidEmailsDomainReject();
};

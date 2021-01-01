/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSCHECKJOBTEST_H
#define CONFIRMADDRESSCHECKJOBTEST_H

#include <QObject>

class ConfirmAddressCheckJobTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmAddressCheckJobTest(QObject *parent = nullptr);
    ~ConfirmAddressCheckJobTest();
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

#endif // CONFIRMADDRESSCHECKJOBTEST_H

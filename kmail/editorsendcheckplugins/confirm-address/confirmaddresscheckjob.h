/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>
#include <QStringList>

class ConfirmAddressCheckJob
{
public:
    ConfirmAddressCheckJob();
    ~ConfirmAddressCheckJob();

    void start();

    void setCheckSettings(const QStringList &domains, const QStringList &whiteEmails, bool rejectedDomain);

    void setAddressList(const QStringList &addressList);

    Q_REQUIRED_RESULT QStringList validEmails() const;

    Q_REQUIRED_RESULT QStringList invalidEmails() const;

private:
    QStringList mAddressList;
    QStringList mValidEmails;
    QStringList mInvalidEmails;
    QStringList mDomains;
    QStringList mWhiteEmails;
    bool mRejectedDomain = false;
};


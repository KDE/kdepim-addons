/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] QStringList validEmails() const;

    [[nodiscard]] QStringList invalidEmails() const;

private:
    QStringList mAddressList;
    QStringList mValidEmails;
    QStringList mInvalidEmails;
    QStringList mDomains;
    QStringList mWhiteEmails;
    bool mRejectedDomain = false;
};

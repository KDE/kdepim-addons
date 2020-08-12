/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSCHECKJOB_H
#define CONFIRMADDRESSCHECKJOB_H

#include <QStringList>
#include <QString>

class ConfirmAddressCheckJob
{
public:
    ConfirmAddressCheckJob();
    ~ConfirmAddressCheckJob();

    void start();

    void setCheckSettings(const QStringList &domains, const QStringList &whiteEmails, bool rejectedDomain);

    void setAddressList(const QStringList &addressList);

    QStringList validEmails() const;

    QStringList invalidEmails() const;

private:
    QStringList mAddressList;
    QStringList mValidEmails;
    QStringList mInvalidEmails;
    QStringList mDomains;
    QStringList mWhiteEmails;
    bool mRejectedDomain = false;
};

#endif // CONFIRMADDRESSCHECKJOB_H

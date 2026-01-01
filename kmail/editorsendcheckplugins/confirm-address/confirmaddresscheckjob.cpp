/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresscheckjob.h"

ConfirmAddressCheckJob::ConfirmAddressCheckJob() = default;

ConfirmAddressCheckJob::~ConfirmAddressCheckJob() = default;

void ConfirmAddressCheckJob::start()
{
    mValidEmails.clear();
    mInvalidEmails.clear();
    bool foundValidEmail = false;
    for (const QString &email : std::as_const(mAddressList)) {
        if (email.isEmpty()) {
            continue;
        }
        foundValidEmail = false;
        if (mRejectedDomain) {
            for (const QString &whiteEmail : std::as_const(mWhiteEmails)) {
                if (email.contains(whiteEmail)) {
                    if (!mValidEmails.contains(email)) {
                        mValidEmails.append(email);
                    }
                    foundValidEmail = true;
                    break;
                }
            }
            if (!foundValidEmail) {
                bool foundRejectedDomain = false;
                for (const QString &domain : std::as_const(mDomains)) {
                    if (email.contains(domain)) {
                        if (!mInvalidEmails.contains(email)) {
                            mInvalidEmails.append(email);
                        }
                        foundRejectedDomain = true;
                        break;
                    }
                }
                if (!foundRejectedDomain) {
                    if (!mValidEmails.contains(email)) {
                        mValidEmails.append(email);
                    }
                }
            }
        } else {
            for (const QString &domain : std::as_const(mDomains)) {
                if (email.contains(domain)) {
                    if (!mValidEmails.contains(email)) {
                        mValidEmails.append(email);
                    }
                    foundValidEmail = true;
                    break;
                }
            }
            if (!foundValidEmail) {
                for (const QString &whiteEmail : std::as_const(mWhiteEmails)) {
                    if (email.contains(whiteEmail)) {
                        if (!mValidEmails.contains(email)) {
                            mValidEmails.append(email);
                        }
                        foundValidEmail = true;
                        break;
                    }
                }
            }
            if (!foundValidEmail) {
                if (!mInvalidEmails.contains(email)) {
                    mInvalidEmails.append(email);
                }
            }
        }
    }
}

void ConfirmAddressCheckJob::setCheckSettings(const QStringList &domains, const QStringList &whiteEmails, bool rejectedDomain)
{
    mDomains = domains;
    mWhiteEmails = whiteEmails;
    mRejectedDomain = rejectedDomain;
}

void ConfirmAddressCheckJob::setAddressList(const QStringList &addressList)
{
    mAddressList = addressList;
}

QStringList ConfirmAddressCheckJob::validEmails() const
{
    return mValidEmails;
}

QStringList ConfirmAddressCheckJob::invalidEmails() const
{
    return mInvalidEmails;
}

/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "confirmaddresscheckjob.h"


ConfirmAddressCheckJob::ConfirmAddressCheckJob()
    : mRejectedDomain(false)
{

}

ConfirmAddressCheckJob::~ConfirmAddressCheckJob()
{

}

void ConfirmAddressCheckJob::start()
{
    mValidEmails.clear();
    mInvalidEmails.clear();
    bool foundValidEmail = false;
    for (const QString &email : qAsConst(mAddressList)) {
        if (email.isEmpty()) {
            continue;
        }
        foundValidEmail = false;
        if (mRejectedDomain) {
            for (const QString &whiteEmail : qAsConst(mWhiteEmails)) {
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
                for (const QString &domain : qAsConst(mDomains)) {
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
            for (const QString &domain : qAsConst(mDomains)) {
                if (email.contains(domain)) {
                    if (!mValidEmails.contains(email)) {
                        mValidEmails.append(email);
                    }
                    foundValidEmail = true;
                    break;
                }
            }
            if (!foundValidEmail) {
                for (const QString &whiteEmail : qAsConst(mWhiteEmails)) {
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

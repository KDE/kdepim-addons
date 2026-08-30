/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresscheckjob.h"
#include <KEmailAddress>
namespace
{
bool matchWhitelistEmail(const QString &email, const QString &whitelistEmail)
{
    return email.compare(whitelistEmail, Qt::CaseInsensitive) == 0;
}

bool matchDomain(const QString &email, const QString &domain)
{
    const int atPos = email.lastIndexOf(u'@');
    if (atPos == -1 || atPos == (email.length() - 1)) {
        return false;
    }

    const QStringView domainPart = QStringView{email}.mid(atPos + 1);
    const QString normalizedDomain = domain.trimmed().startsWith(u'@') ? domain.trimmed().mid(1) : domain.trimmed();
    if (normalizedDomain.isEmpty()) {
        return false;
    }

    if (domainPart.compare(normalizedDomain, Qt::CaseInsensitive) == 0) {
        return true;
    }

    const QString suffix = u'.' + normalizedDomain;
    return domainPart.endsWith(suffix, Qt::CaseInsensitive);
}
}

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
        // The composer hands us full mailboxes ("Name <foo@kde.org>"). Store the bare address:
        // it's what the whitelist is compared against when it's written back to the config.
        const QString extractedAddress = KEmailAddress::extractEmailAddress(email);
        // Keep the original text when nothing could be extracted, so the user still sees what was typed.
        const QString addr = extractedAddress.isEmpty() ? email.trimmed() : extractedAddress;
        foundValidEmail = false;
        if (mRejectedDomain) {
            for (const QString &whiteEmail : std::as_const(mWhiteEmails)) {
                if (matchWhitelistEmail(addr, whiteEmail)) {
                    if (!mValidEmails.contains(addr)) {
                        mValidEmails.append(addr);
                    }
                    foundValidEmail = true;
                    break;
                }
            }
            if (!foundValidEmail) {
                bool foundRejectedDomain = false;
                for (const QString &domain : std::as_const(mDomains)) {
                    if (matchDomain(addr, domain)) {
                        if (!mInvalidEmails.contains(addr)) {
                            mInvalidEmails.append(addr);
                        }
                        foundRejectedDomain = true;
                        break;
                    }
                }
                if (!foundRejectedDomain) {
                    if (!mValidEmails.contains(addr)) {
                        mValidEmails.append(addr);
                    }
                }
            }
        } else {
            for (const QString &domain : std::as_const(mDomains)) {
                if (matchDomain(addr, domain)) {
                    if (!mValidEmails.contains(addr)) {
                        mValidEmails.append(addr);
                    }
                    foundValidEmail = true;
                    break;
                }
            }
            if (!foundValidEmail) {
                for (const QString &whiteEmail : std::as_const(mWhiteEmails)) {
                    if (matchWhitelistEmail(addr, whiteEmail)) {
                        if (!mValidEmails.contains(addr)) {
                            mValidEmails.append(addr);
                        }
                        foundValidEmail = true;
                        break;
                    }
                }
            }
            if (!foundValidEmail) {
                if (!mInvalidEmails.contains(addr)) {
                    mInvalidEmails.append(addr);
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

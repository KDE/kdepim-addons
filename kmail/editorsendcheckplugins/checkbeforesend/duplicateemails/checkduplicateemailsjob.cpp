/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkduplicateemailsjob.h"

#include <KEmailAddress>
#include <PimCommon/PimUtil>

CheckDuplicateEmailsJob::CheckDuplicateEmailsJob() = default;

CheckDuplicateEmailsJob::~CheckDuplicateEmailsJob() = default;

void CheckDuplicateEmailsJob::start()
{
    mResult.clear();
    if (mEmails.isEmpty()) {
        return;
    }
    QMap<QString, int> results;
    for (const QString &email : std::as_const(mEmails)) {
        QString tname;
        QString temail;
        KEmailAddress::extractEmailAddressAndName(email, temail, tname); // ignore return value

        if (!temail.isEmpty()) {
            const int val = results.value(temail, 0);
            if (val == 0) {
                results.insert(temail, val + 1);
            } else {
                results[temail] = val + 1;
            }
        }
    }
    QMapIterator<QString, int> i(results);
    while (i.hasNext()) {
        i.next();
        if (i.value() > 1) {
            mResult.insert(i.key(), i.value());
        }
    }
}

void CheckDuplicateEmailsJob::setEmails(const QStringList &list)
{
    mEmails = PimCommon::Util::generateEmailList(list);
}

QMap<QString, int> CheckDuplicateEmailsJob::result() const
{
    return mResult;
}

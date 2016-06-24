/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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
#include "checkduplicateemailsjob.h"
#include <KEmailAddress>

CheckDuplicateEmailsJob::CheckDuplicateEmailsJob()
{

}

CheckDuplicateEmailsJob::~CheckDuplicateEmailsJob()
{

}

void CheckDuplicateEmailsJob::start()
{
    mResult.clear();
    if (mEmails.isEmpty()) {
        return;
    }
    QMap<QString, int> results;
    Q_FOREACH (const QString &email, mEmails) {
        QString tname, temail;
        KEmailAddress::extractEmailAddressAndName(email, temail, tname);    // ignore return value

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
    mEmails = list;
}

QMap<QString, int> CheckDuplicateEmailsJob::result() const
{
    return mResult;
}

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

#include "checkattachmentjob.h"
#include <KEmailAddress>

CheckAttachmentJob::CheckAttachmentJob()
{

}

CheckAttachmentJob::~CheckAttachmentJob()
{

}

void CheckAttachmentJob::start()
{
    mResultList.clear();

    Q_FOREACH (const QString &email, mOriginalEmails) {
        QString tname, temail;
        KEmailAddress::extractEmailAddressAndName(email, temail, tname);    // ignore return value
        if (!temail.isEmpty()) {
            if (!mResultList.contains(temail)) {
                mResultList.append(temail);
            }
        }
    }
}

QStringList CheckAttachmentJob::originalEmails() const
{
    return mOriginalEmails;
}

void CheckAttachmentJob::setOriginalEmails(const QStringList &originalEmails)
{
    mOriginalEmails = originalEmails;
}

QStringList CheckAttachmentJob::resultList() const
{
    return mResultList;
}

void CheckAttachmentJob::setResultList(const QStringList &resultList)
{
    mResultList = resultList;
}

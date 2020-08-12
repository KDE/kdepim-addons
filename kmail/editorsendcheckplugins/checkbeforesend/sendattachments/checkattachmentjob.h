/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKATTACHMENTJOB_H
#define CHECKATTACHMENTJOB_H

#include <QStringList>

class CheckAttachmentJob
{
public:
    CheckAttachmentJob();
    ~CheckAttachmentJob();

    void start();

    Q_REQUIRED_RESULT QStringList originalEmails() const;
    void setOriginalEmails(const QStringList &originalEmails);

    Q_REQUIRED_RESULT QStringList resultList() const;
    void setResultList(const QStringList &resultList);

private:
    QStringList mOriginalEmails;
    QStringList mResultList;
};

#endif // CHECKATTACHMENTJOB_H

/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKDUPLICATEEMAILSJOB_H
#define CHECKDUPLICATEEMAILSJOB_H

#include <QMap>
#include <QStringList>

class CheckDuplicateEmailsJob
{
public:
    CheckDuplicateEmailsJob();
    ~CheckDuplicateEmailsJob();

    void start();

    void setEmails(const QStringList &list);
    Q_REQUIRED_RESULT QMap<QString, int> result() const;

private:
    QStringList mEmails;
    QMap<QString, int> mResult;
};

#endif // CHECKDUPLICATEEMAILSJOB_H

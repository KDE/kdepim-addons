/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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


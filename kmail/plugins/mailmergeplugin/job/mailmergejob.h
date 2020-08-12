/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef MAILMERGEJOB_H
#define MAILMERGEJOB_H

#include <QObject>
namespace MailMerge {
class MailMergeJob : public QObject
{
    Q_OBJECT
public:
    explicit MailMergeJob(QObject *parent = nullptr);
    ~MailMergeJob();
    void start();
};
}

#endif // MAILMERGEJOB_H

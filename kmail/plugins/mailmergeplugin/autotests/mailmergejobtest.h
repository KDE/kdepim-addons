/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef MAILMERGEJOBTEST_H
#define MAILMERGEJOBTEST_H

#include <QObject>

class MailMergeJobTest : public QObject
{
    Q_OBJECT
public:
    explicit MailMergeJobTest(QObject *parent = nullptr);
    ~MailMergeJobTest() override;
};

#endif // MAILMERGEJOBTEST_H

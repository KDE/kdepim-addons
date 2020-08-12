/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKDUPLICATEEMAILSJOBTEST_H
#define CHECKDUPLICATEEMAILSJOBTEST_H

#include <QObject>

class CheckDuplicateEmailsJobTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckDuplicateEmailsJobTest(QObject *parent = nullptr);
    ~CheckDuplicateEmailsJobTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldReturnEmptyListWhenEmailsListIsEmpty();
    void shouldReturnEmails_data();
    void shouldReturnEmails();
};

#endif // CHECKDUPLICATEEMAILSJOBTEST_H

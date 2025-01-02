/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CheckDuplicateEmailsJobTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckDuplicateEmailsJobTest(QObject *parent = nullptr);
    ~CheckDuplicateEmailsJobTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldReturnEmptyListWhenEmailsListIsEmpty();
    void shouldReturnEmails_data();
    void shouldReturnEmails();
};

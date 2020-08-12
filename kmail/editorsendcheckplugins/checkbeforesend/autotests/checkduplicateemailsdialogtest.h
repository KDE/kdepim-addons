/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKDUPLICATEEMAILSDIALOGTEST_H
#define CHECKDUPLICATEEMAILSDIALOGTEST_H

#include <QObject>

class CheckDuplicateEmailsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckDuplicateEmailsDialogTest(QObject *parent = nullptr);
    ~CheckDuplicateEmailsDialogTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddEmails();
};

#endif // CHECKDUPLICATEEMAILSDIALOGTEST_H

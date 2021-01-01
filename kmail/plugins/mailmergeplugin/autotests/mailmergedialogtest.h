/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef MAILMERGEDIALOGTEST_H
#define MAILMERGEDIALOGTEST_H

#include <QObject>

class MailMergeDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MailMergeDialogTest(QObject *parent = nullptr);
    ~MailMergeDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MAILMERGEDIALOGTEST_H

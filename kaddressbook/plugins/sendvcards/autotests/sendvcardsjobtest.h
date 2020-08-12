/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SENDVCARDSJOBTEST_H
#define SENDVCARDSJOBTEST_H

#include <QObject>

class SendVcardsJobTest : public QObject
{
    Q_OBJECT
public:
    explicit SendVcardsJobTest(QObject *parent = nullptr);
    ~SendVcardsJobTest();
private Q_SLOTS:
    void shouldNotStartWhenListAddressIsEmpty();
    void shouldHasDefaultValue();
    void shouldChangeExportVersion();
};

#endif // SENDVCARDSJOBTEST_H

/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class SendVcardsJobTest : public QObject
{
    Q_OBJECT
public:
    explicit SendVcardsJobTest(QObject *parent = nullptr);
    ~SendVcardsJobTest() override;
private Q_SLOTS:
    void shouldNotStartWhenListAddressIsEmpty();
    void shouldHasDefaultValue();
    void shouldChangeExportVersion();
};

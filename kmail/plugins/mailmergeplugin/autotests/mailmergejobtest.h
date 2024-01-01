/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class MailMergeJobTest : public QObject
{
    Q_OBJECT
public:
    explicit MailMergeJobTest(QObject *parent = nullptr);
    ~MailMergeJobTest() override;
};

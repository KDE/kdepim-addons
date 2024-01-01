/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>
namespace MailMerge
{
class MailMergeJob : public QObject
{
    Q_OBJECT
public:
    explicit MailMergeJob(QObject *parent = nullptr);
    ~MailMergeJob() override;
    void start();
};
}

/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class MailMergeDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MailMergeDialogTest(QObject *parent = nullptr);
    ~MailMergeDialogTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

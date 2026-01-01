/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class SelectAttachmentDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectAttachmentDialogTest(QObject *parent = nullptr);
    ~SelectAttachmentDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

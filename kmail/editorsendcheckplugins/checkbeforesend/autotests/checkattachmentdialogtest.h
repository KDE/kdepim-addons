/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CheckAttachmentDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckAttachmentDialogTest(QObject *parent = nullptr);
    ~CheckAttachmentDialogTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddEmails();
};

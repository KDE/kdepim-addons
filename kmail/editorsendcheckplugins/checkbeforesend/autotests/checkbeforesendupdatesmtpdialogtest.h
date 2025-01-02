/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CheckBeforeSendUpdateSmtpDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckBeforeSendUpdateSmtpDialogTest(QObject *parent = nullptr);
    ~CheckBeforeSendUpdateSmtpDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

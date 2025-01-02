/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TemplateParserEmailAddressRequesterAkonadiTest : public QObject
{
    Q_OBJECT
public:
    explicit TemplateParserEmailAddressRequesterAkonadiTest(QObject *parent = nullptr);
    ~TemplateParserEmailAddressRequesterAkonadiTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEmitSignal();
    void shouldClearValue();
    void shouldAssignValue();
};

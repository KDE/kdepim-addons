/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ConfirmBeforeDeletingCreateRuleWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingCreateRuleWidgetTest(QObject *parent = nullptr);
    ~ConfirmBeforeDeletingCreateRuleWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

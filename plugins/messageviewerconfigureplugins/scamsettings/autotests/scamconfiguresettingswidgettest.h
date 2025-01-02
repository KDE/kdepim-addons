/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ScamConfigureSettingsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ScamConfigureSettingsWidgetTest(QObject *parent = nullptr);
    ~ScamConfigureSettingsWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class ScamConfigureSettingsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ScamConfigureSettingsDialogTest(QObject *parent = nullptr);
    ~ScamConfigureSettingsDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LanguageToolUpdateComboBoxTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolUpdateComboBoxTest(QObject *parent = nullptr);
    ~LanguageToolUpdateComboBoxTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};


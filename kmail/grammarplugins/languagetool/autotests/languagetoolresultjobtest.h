/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LanguageToolResultJobTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolResultJobTest(QObject *parent = nullptr);
    ~LanguageToolResultJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToStart();
};


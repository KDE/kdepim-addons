/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LanguageInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageInfoTest(QObject *parent = nullptr);
    ~LanguageInfoTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};


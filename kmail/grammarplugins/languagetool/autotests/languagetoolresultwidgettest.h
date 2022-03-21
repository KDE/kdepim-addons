/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class LanguageToolResultWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolResultWidgetTest(QObject *parent = nullptr);
    ~LanguageToolResultWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

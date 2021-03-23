/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LanguageToolConfigWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolConfigWidgetTest(QObject *parent = nullptr);
    ~LanguageToolConfigWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldUpdateWidgets();
};


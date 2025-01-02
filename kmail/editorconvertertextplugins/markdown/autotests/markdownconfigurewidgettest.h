/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MarkdownConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownConfigureWidgetTest(QObject *parent = nullptr);
    ~MarkdownConfigureWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

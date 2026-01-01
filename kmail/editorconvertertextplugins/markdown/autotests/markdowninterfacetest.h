/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MarkdownInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownInterfaceTest(QObject *parent = nullptr);
    ~MarkdownInterfaceTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MergeContactWidgetListTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactWidgetListTest(QObject *parent = nullptr);
    ~MergeContactWidgetListTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCleanListWhenSetItems();
};

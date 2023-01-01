/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AdBlockBlockableItemsJobTest : public QObject
{
    Q_OBJECT
public:
    explicit AdBlockBlockableItemsJobTest(QObject *parent = nullptr);
    ~AdBlockBlockableItemsJobTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldReturnEmptyListWhenWebEngineIsNotSet();
    void shouldReturnAddBlockItem();
};

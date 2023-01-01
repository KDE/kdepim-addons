/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class AdBlockResultTest : public QObject
{
    Q_OBJECT
public:
    explicit AdBlockResultTest(QObject *parent = nullptr);
    ~AdBlockResultTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeValid();
};

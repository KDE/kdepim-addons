/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class SelectMailDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectMailDialogTest(QObject *parent = nullptr);
    ~SelectMailDialogTest() override = default;
};

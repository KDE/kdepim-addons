/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class OpenUrlWithConfigureCreateDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureCreateDialogTest(QObject *parent = nullptr);
    ~OpenUrlWithConfigureCreateDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

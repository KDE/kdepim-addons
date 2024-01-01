/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GravatarUpdateDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit GravatarUpdateDialogTest(QObject *parent = nullptr);
    ~GravatarUpdateDialogTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

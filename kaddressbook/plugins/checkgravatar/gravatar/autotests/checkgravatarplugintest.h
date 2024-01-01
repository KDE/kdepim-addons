/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class CheckGravatarPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckGravatarPluginTest(QObject *parent = nullptr);
    ~CheckGravatarPluginTest() override = default;
};

/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ExpertPluginInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit ExpertPluginInterfaceTest(QObject *parent = nullptr);
    ~ExpertPluginInterfaceTest() override = default;
};

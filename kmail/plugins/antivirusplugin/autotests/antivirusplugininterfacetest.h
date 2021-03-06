/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AntiVirusPluginInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit AntiVirusPluginInterfaceTest(QObject *parent = nullptr);
    ~AntiVirusPluginInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateAction();
    void shouldEmitActivatedSignal();
};


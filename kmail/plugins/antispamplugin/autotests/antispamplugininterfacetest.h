/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AntiSpamPluginInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit AntiSpamPluginInterfaceTest(QObject *parent = nullptr);
    ~AntiSpamPluginInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateAction();
    void shouldEmitActivatedSignal();
};

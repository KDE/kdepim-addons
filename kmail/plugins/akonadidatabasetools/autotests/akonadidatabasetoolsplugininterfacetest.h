/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AkonadiDatabaseToolsPluginInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit AkonadiDatabaseToolsPluginInterfaceTest(QObject *parent = nullptr);
    ~AkonadiDatabaseToolsPluginInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateAction();
    // void shouldEmitActivatedSignal();
};

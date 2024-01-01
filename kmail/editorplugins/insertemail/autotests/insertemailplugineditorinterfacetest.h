/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class InsertEmailPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertEmailPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~InsertEmailPluginEditorInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

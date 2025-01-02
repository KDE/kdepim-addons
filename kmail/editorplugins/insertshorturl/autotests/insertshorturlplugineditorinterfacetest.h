/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class InsertShorturlPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertShorturlPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~InsertShorturlPluginEditorInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

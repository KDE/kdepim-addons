/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class NonBreakingSpacePluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit NonBreakingSpacePluginEditorInterfaceTest(QObject *parent = nullptr);
    ~NonBreakingSpacePluginEditorInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

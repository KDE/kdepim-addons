/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class EnterpriseHeaderStylePluginTest : public QObject
{
    Q_OBJECT
public:
    explicit EnterpriseHeaderStylePluginTest(QObject *parent = nullptr);
    ~EnterpriseHeaderStylePluginTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateInterface();
    void testFormatEmpty();
    void testFormat_data();
    void testFormat();
};

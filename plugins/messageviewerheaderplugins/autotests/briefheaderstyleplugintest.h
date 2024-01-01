/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class BriefHeaderStylePluginTest : public QObject
{
    Q_OBJECT
public:
    explicit BriefHeaderStylePluginTest(QObject *parent = nullptr);
    ~BriefHeaderStylePluginTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateInterface();
    void testFormatEmpty();
    void testFormat_data();
    void testFormat();
};

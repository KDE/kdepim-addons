/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ViewerPluginExternalScriptInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptInfoTest(QObject *parent = nullptr);
    ~ViewerPluginExternalScriptInfoTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldHaveValid();
    void shouldBeEqual_data();
    void shouldBeEqual();
};

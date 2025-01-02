/*
    SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class DoNotTrackPluginUrlInterceptorTest : public QObject
{
    Q_OBJECT
public:
    explicit DoNotTrackPluginUrlInterceptorTest(QObject *parent = nullptr);
    ~DoNotTrackPluginUrlInterceptorTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

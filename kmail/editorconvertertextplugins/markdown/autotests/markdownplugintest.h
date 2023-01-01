/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MarkdownPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownPluginTest(QObject *parent = nullptr);
    ~MarkdownPluginTest() override = default;
private Q_SLOTS:
    void shouldCreateInterface();
};

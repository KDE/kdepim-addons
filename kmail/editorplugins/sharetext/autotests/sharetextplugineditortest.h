/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ShareTextPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit ShareTextPluginEditorTest(QObject *parent = nullptr);
    ~ShareTextPluginEditorTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

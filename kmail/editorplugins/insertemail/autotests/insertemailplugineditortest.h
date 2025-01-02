/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class InsertEmailPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertEmailPluginEditorTest(QObject *parent = nullptr);
    ~InsertEmailPluginEditorTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

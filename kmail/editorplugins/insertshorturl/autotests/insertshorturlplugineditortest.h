/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class InsertShorturlPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertShorturlPluginEditorTest(QObject *parent = nullptr);
    ~InsertShorturlPluginEditorTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AutoCorrectionPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit AutoCorrectionPluginEditorTest(QObject *parent = nullptr);
    ~AutoCorrectionPluginEditorTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

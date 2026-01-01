/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AutoCorrectionPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit AutoCorrectionPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~AutoCorrectionPluginEditorInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

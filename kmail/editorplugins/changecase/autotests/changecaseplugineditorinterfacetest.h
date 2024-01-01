/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class ChangeCasePluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit ChangeCasePluginEditorInterfaceTest(QObject *parent = nullptr);
    ~ChangeCasePluginEditorInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

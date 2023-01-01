/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class ShareTextPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit ShareTextPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~ShareTextPluginEditorInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

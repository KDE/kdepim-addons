/*
   SPDX-FileCopyrightText: 2020-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class FolderConfigureSettingsWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsWidgetTest(QObject *parent = nullptr);
    ~FolderConfigureSettingsWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

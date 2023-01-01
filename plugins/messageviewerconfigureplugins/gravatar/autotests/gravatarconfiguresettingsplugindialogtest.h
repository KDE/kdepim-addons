/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GravatarConfigureSettingsPluginDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit GravatarConfigureSettingsPluginDialogTest(QObject *parent = nullptr);
    ~GravatarConfigureSettingsPluginDialogTest() override = default;
};

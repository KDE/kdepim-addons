/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <PimCommon/ConfigurePluginDialog>

class GravatarConfigureSettingsPluginWidget;
class GravatarConfigureSettingsPluginDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit GravatarConfigureSettingsPluginDialog(QWidget *parent = nullptr);
    ~GravatarConfigureSettingsPluginDialog() override;

    Q_REQUIRED_RESULT QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;

private:
    GravatarConfigureSettingsPluginWidget *mWidget = nullptr;
};

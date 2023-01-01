/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarconfiguresettingsplugindialog.h"
#include "gravatarconfiguresettingspluginwidget.h"
#include <KLocalizedString>

GravatarConfigureSettingsPluginDialog::GravatarConfigureSettingsPluginDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Gravatar"));
    initLayout(true);
}

GravatarConfigureSettingsPluginDialog::~GravatarConfigureSettingsPluginDialog() = default;

QWidget *GravatarConfigureSettingsPluginDialog::createLayout()
{
    mWidget = new GravatarConfigureSettingsPluginWidget(this);
    return mWidget;
}

void GravatarConfigureSettingsPluginDialog::save()
{
    mWidget->saveSettings();
}

void GravatarConfigureSettingsPluginDialog::load()
{
    mWidget->loadSettings();
}

void GravatarConfigureSettingsPluginDialog::reset()
{
    mWidget->resetSettings();
}

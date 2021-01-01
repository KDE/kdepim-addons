/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRAVATARCONFIGURESETTINGSPLUGINDIALOG_H
#define GRAVATARCONFIGURESETTINGSPLUGINDIALOG_H

#include <PimCommon/ConfigurePluginDialog>

class GravatarConfigureSettingsPluginWidget;
class GravatarConfigureSettingsPluginDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit GravatarConfigureSettingsPluginDialog(QWidget *parent = nullptr);
    ~GravatarConfigureSettingsPluginDialog() override;

    QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
private:
    GravatarConfigureSettingsPluginWidget *mWidget = nullptr;
};

#endif // GRAVATARCONFIGURESETTINGSPLUGINDIALOG_H

/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/ConfigurePluginDialog>
class ViewerPluginExternalConfigureWidget;
class ViewerPluginExternalConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalConfigureDialog(QWidget *parent = nullptr);
    ~ViewerPluginExternalConfigureDialog() override;

protected:
    [[nodiscard]] QWidget *createLayout() override;
    void save() override;
    void load() override;
    void help() override;

private:
    ViewerPluginExternalConfigureWidget *mConfigWidget = nullptr;
};

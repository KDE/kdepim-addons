/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libadblockplugin_export.h"
#include <PimCommon/ConfigurePluginDialog>
class QWidget;

class AdblockPluginUrlInterceptorConfigureWidget;
class LIBADBLOCKPLUGIN_EXPORT AdblockPluginUrlInterceptorConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorConfigureDialog(QWidget *parent = nullptr);
    ~AdblockPluginUrlInterceptorConfigureDialog() override;

protected:
    [[nodiscard]] QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;

private:
    LIBADBLOCKPLUGIN_NO_EXPORT void readConfig();
    LIBADBLOCKPLUGIN_NO_EXPORT void writeConfig();
    AdblockPluginUrlInterceptorConfigureWidget *mAdblockConfigureWidget = nullptr;
};

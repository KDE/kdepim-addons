/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKPLUGINURLINTERCEPTORCONFIGUREDIALOG_H
#define ADBLOCKPLUGINURLINTERCEPTORCONFIGUREDIALOG_H

#include <PimCommon/ConfigurePluginDialog>
#include <QWidget>
#include "adblocklib_export.h"

namespace AdBlock {
class AdblockPluginUrlInterceptorConfigureWidget;
class ADBLOCKLIB_EXPORT AdblockPluginUrlInterceptorConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorConfigureDialog(QWidget *parent = nullptr);
    ~AdblockPluginUrlInterceptorConfigureDialog() override;

protected:
    QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;
private:
    AdblockPluginUrlInterceptorConfigureWidget *mAdblockConfigureWidget = nullptr;
};
}
#endif // ADBLOCKPLUGINURLINTERCEPTORCONFIGUREDIALOG_H

/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockplugin_private_export.h"
#include "adblockpluginurlinterceptoraddadblocklistwidget.h"
#include <QDialog>
class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockPluginUrlInterceptorAddAdblockListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorAddAdblockListDialog(QWidget *parent = nullptr);
    ~AdblockPluginUrlInterceptorAddAdblockListDialog() override;

    [[nodiscard]] AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info() const;
    void setInfo(const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo &adblockInfo);

private:
    AdblockPluginUrlInterceptorAddAdblockListWidget *const mAddAdblockListWidget;
};

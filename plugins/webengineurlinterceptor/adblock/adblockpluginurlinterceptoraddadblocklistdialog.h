/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockplugin_private_export.h"
#include <QDialog>
class AdblockPluginUrlInterceptorAddAdblockListWidget;
class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockPluginUrlInterceptorAddAdblockListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorAddAdblockListDialog(QWidget *parent = nullptr);
    ~AdblockPluginUrlInterceptorAddAdblockListDialog() override;

private:
    AdblockPluginUrlInterceptorAddAdblockListWidget *const mAddAdblockListWidget;
};

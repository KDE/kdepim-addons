/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockplugin_private_export.h"
#include <QDialog>
class AdblockViewFilterWidget;
class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockViewFilterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdblockViewFilterDialog(QWidget *parent = nullptr);
    ~AdblockViewFilterDialog() override;

private:
    void readConfig();
    void writeConfig();
    AdblockViewFilterWidget *const mAdblockViewFilterWidget;
};

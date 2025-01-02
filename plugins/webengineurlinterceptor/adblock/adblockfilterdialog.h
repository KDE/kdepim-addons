/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "adblockplugin_private_export.h"
#include <QDialog>
class AdblockFilterWidget;
class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockFilterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdblockFilterDialog(QWidget *parent = nullptr);
    ~AdblockFilterDialog() override;

    void loadSettings();

private:
    LIBADBLOCKPLUGIN_NO_EXPORT void readConfig();
    LIBADBLOCKPLUGIN_NO_EXPORT void writeConfig();
    AdblockFilterWidget *const mAdblockFilterWidget;
};

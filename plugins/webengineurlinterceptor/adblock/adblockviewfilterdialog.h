/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

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

    void setFilterText(const QString &str);

private:
    LIBADBLOCKPLUGIN_NO_EXPORT void readConfig();
    LIBADBLOCKPLUGIN_NO_EXPORT void writeConfig();
    AdblockViewFilterWidget *const mAdblockViewFilterWidget;
};

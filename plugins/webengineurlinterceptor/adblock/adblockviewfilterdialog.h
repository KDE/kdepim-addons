/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class AdblockViewFilterWidget;
class AdblockViewFilterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdblockViewFilterDialog(QWidget *parent = nullptr);
    ~AdblockViewFilterDialog() override;

private:
    AdblockViewFilterWidget *const mAdblockViewFilterWidget;
};
/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "confirmbeforedeleting_private_export.h"
#include <QDialog>
class ConfirmBeforeDeletingWidget;
class KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT ConfirmBeforeDeletingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingDialog(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingDialog() override;

private:
    void writeConfig();
    void readConfig();
    ConfirmBeforeDeletingWidget *const mConfirmBeforeDeletingWidget;
};

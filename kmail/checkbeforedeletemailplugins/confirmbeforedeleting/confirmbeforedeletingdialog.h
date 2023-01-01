/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "kmailconfirmbeforedeleting_export.h"
#include <QDialog>
class ConfirmBeforeDeletingWidget;
class KMAILCONFIRMBEFOREDELETING_EXPORT ConfirmBeforeDeletingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingDialog(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingDialog() override;

private:
    void slotSave();
    void writeConfig();
    void readConfig();
    ConfirmBeforeDeletingWidget *const mConfirmBeforeDeletingWidget;
};

/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

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
    KMAILCONFIRMBEFOREDELETING_NO_EXPORT void slotSave();
    KMAILCONFIRMBEFOREDELETING_NO_EXPORT void writeConfig();
    KMAILCONFIRMBEFOREDELETING_NO_EXPORT void readConfig();
    ConfirmBeforeDeletingWidget *const mConfirmBeforeDeletingWidget;
};

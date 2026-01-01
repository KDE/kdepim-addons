/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "confirmbeforedeleting_private_export.h"
#include "confirmbeforedeletingcreaterulewidget.h"
#include <QDialog>
class KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT ConfirmBeforeDeletingCreateRuleDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingCreateRuleDialog(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingCreateRuleDialog() override;

    [[nodiscard]] ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info() const;

    void setInfo(const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo &info);

private:
    ConfirmBeforeDeletingCreateRuleWidget *const mConfirmBeforeDeletingCreateRuleWidget;
};

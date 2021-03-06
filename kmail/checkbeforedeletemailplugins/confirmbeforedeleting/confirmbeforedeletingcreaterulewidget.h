/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include "confirmbeforedeleting_private_export.h"
class QLineEdit;
class QComboBox;
class KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT ConfirmBeforeDeletingCreateRuleWidget : public QWidget
{
    Q_OBJECT
public:
    struct ConfirmBeforeDeletingInfo {
        QString pattern;
        QString ruleType;
    };
    explicit ConfirmBeforeDeletingCreateRuleWidget(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingCreateRuleWidget() override;
    Q_REQUIRED_RESULT ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info() const;

    void setInfo(const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo &info);

Q_SIGNALS:
    void updateOkButton(bool enabled);

private:
    void fillComboBox();
    QLineEdit *const mPatternLineEdit;
    QComboBox *const mRuleTypeComboBox;
};

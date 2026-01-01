/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

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
        ConfirmBeforeDeletingInfo(const QString &p, const QString &type)
            : pattern(p)
            , ruleType(type)
        {
        }
        QString pattern;
        QString ruleType;
        [[nodiscard]] bool operator==(const ConfirmBeforeDeletingInfo &other) const;
        [[nodiscard]] bool operator!=(const ConfirmBeforeDeletingInfo &other) const;
    };
    explicit ConfirmBeforeDeletingCreateRuleWidget(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingCreateRuleWidget() override;
    [[nodiscard]] ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info() const;

    void setInfo(const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo &info);

Q_SIGNALS:
    void updateOkButton(bool enabled);

private:
    KMAILCONFIRMBEFOREDELETING_NO_EXPORT void slotRuleTypeChanged(int index);
    KMAILCONFIRMBEFOREDELETING_NO_EXPORT void fillComboBox();
    QLineEdit *const mPatternLineEdit;
    QComboBox *const mRuleTypeComboBox;
};

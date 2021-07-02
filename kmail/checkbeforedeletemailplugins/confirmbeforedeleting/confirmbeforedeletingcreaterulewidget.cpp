/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingcreaterulewidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingCreateRuleWidget(QWidget *parent)
    : QWidget(parent)
    , mPatternLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    auto label = new QLabel(i18n("Pattern"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mPatternLineEdit->setObjectName(QStringLiteral("mPatternLineEdit"));
    mainLayout->addWidget(mPatternLineEdit);
}

ConfirmBeforeDeletingCreateRuleWidget::~ConfirmBeforeDeletingCreateRuleWidget()
{
}

ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo ConfirmBeforeDeletingCreateRuleWidget::info() const
{
    ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info;
    return info;
}

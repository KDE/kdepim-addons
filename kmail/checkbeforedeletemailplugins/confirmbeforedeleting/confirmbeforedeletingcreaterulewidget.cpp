/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingcreaterulewidget.h"
#include <KLocalizedString>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingCreateRuleWidget(QWidget *parent)
    : QWidget(parent)
    , mPatternLineEdit(new QLineEdit(this))
    , mRuleTypeComboBox(new QComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mRuleTypeComboBox->setObjectName(QStringLiteral("mRuleTypeComboBox"));
    mainLayout->addWidget(mRuleTypeComboBox);

    auto label = new QLabel(i18n("Pattern:"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mPatternLineEdit->setObjectName(QStringLiteral("mPatternLineEdit"));
    mainLayout->addWidget(mPatternLineEdit);
    fillComboBox();
}

ConfirmBeforeDeletingCreateRuleWidget::~ConfirmBeforeDeletingCreateRuleWidget()
{
}

ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo ConfirmBeforeDeletingCreateRuleWidget::info() const
{
    ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info;
    info.pattern = mPatternLineEdit->text();
    info.ruleType = mRuleTypeComboBox->currentData().toString();
    return info;
}

void ConfirmBeforeDeletingCreateRuleWidget::setInfo(const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo &info)
{
    mPatternLineEdit->setText(info.pattern);
    mRuleTypeComboBox->setCurrentIndex(mRuleTypeComboBox->findData(info.ruleType));
}

void ConfirmBeforeDeletingCreateRuleWidget::fillComboBox()
{
    mRuleTypeComboBox->addItem(i18n("Body"), QStringLiteral("body"));
    mRuleTypeComboBox->addItem(i18n("Subject"), QStringLiteral("subject"));
    mRuleTypeComboBox->addItem(i18n("To"), QStringLiteral("to"));
    mRuleTypeComboBox->addItem(i18n("Cc"), QStringLiteral("cc"));
}

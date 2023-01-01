/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingcreateruledialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

ConfirmBeforeDeletingCreateRuleDialog::ConfirmBeforeDeletingCreateRuleDialog(QWidget *parent)
    : QDialog(parent)
    , mConfirmBeforeDeletingCreateRuleWidget(new ConfirmBeforeDeletingCreateRuleWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Rule"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfirmBeforeDeletingCreateRuleWidget->setObjectName(QStringLiteral("mConfirmBeforeDeletingCreateRuleWidget"));
    mainLayout->addWidget(mConfirmBeforeDeletingCreateRuleWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfirmBeforeDeletingCreateRuleDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfirmBeforeDeletingCreateRuleDialog::reject);
    auto okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);
    connect(mConfirmBeforeDeletingCreateRuleWidget, &ConfirmBeforeDeletingCreateRuleWidget::updateOkButton, okButton, &QPushButton::setEnabled);
}

ConfirmBeforeDeletingCreateRuleDialog::~ConfirmBeforeDeletingCreateRuleDialog() = default;

ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo ConfirmBeforeDeletingCreateRuleDialog::info() const
{
    return mConfirmBeforeDeletingCreateRuleWidget->info();
}

void ConfirmBeforeDeletingCreateRuleDialog::setInfo(const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo &info)
{
    mConfirmBeforeDeletingCreateRuleWidget->setInfo(info);
}

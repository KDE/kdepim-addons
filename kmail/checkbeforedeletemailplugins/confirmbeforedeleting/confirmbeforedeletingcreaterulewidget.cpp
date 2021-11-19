/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingcreaterulewidget.h"
#include "confirmbeforedeletingrule.h"
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
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    auto label = new QLabel(i18n("Type:"), this);
    label->setObjectName(QStringLiteral("typeLabel"));
    mainLayout->addWidget(label);

    mRuleTypeComboBox->setObjectName(QStringLiteral("mRuleTypeComboBox"));
    mainLayout->addWidget(mRuleTypeComboBox);

    label = new QLabel(i18n("Contains:"), this);
    label->setObjectName(QStringLiteral("containsLabel"));
    mainLayout->addWidget(label);

    mPatternLineEdit->setObjectName(QStringLiteral("mPatternLineEdit"));
    mPatternLineEdit->setClearButtonEnabled(true);
    mainLayout->addWidget(mPatternLineEdit);
    fillComboBox();
    connect(mPatternLineEdit, &QLineEdit::textChanged, this, [this](const QString &str) {
        Q_EMIT updateOkButton(!str.trimmed().isEmpty());
    });
}

ConfirmBeforeDeletingCreateRuleWidget::~ConfirmBeforeDeletingCreateRuleWidget()
{
}

ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo ConfirmBeforeDeletingCreateRuleWidget::info() const
{
    const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info(mPatternLineEdit->text(), mRuleTypeComboBox->currentData().toString());
    return info;
}

void ConfirmBeforeDeletingCreateRuleWidget::setInfo(const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo &info)
{
    mPatternLineEdit->setText(info.pattern);
    mRuleTypeComboBox->setCurrentIndex(mRuleTypeComboBox->findData(info.ruleType));
}

void ConfirmBeforeDeletingCreateRuleWidget::fillComboBox()
{
    mRuleTypeComboBox->addItem(i18n("Body"), ConfirmBeforeDeletingRule::ruleTypeToString(ConfirmBeforeDeletingRule::Body));
    mRuleTypeComboBox->addItem(i18n("Subject"), ConfirmBeforeDeletingRule::ruleTypeToString(ConfirmBeforeDeletingRule::Subject));
    mRuleTypeComboBox->addItem(i18n("To"), ConfirmBeforeDeletingRule::ruleTypeToString(ConfirmBeforeDeletingRule::To));
    mRuleTypeComboBox->addItem(i18n("Cc"), ConfirmBeforeDeletingRule::ruleTypeToString(ConfirmBeforeDeletingRule::Cc));
    mRuleTypeComboBox->addItem(i18n("Bcc"), ConfirmBeforeDeletingRule::ruleTypeToString(ConfirmBeforeDeletingRule::Bcc));
}

bool ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo::operator==(const ConfirmBeforeDeletingInfo &other) const
{
    return other.pattern != pattern && other.ruleType != ruleType;
}

bool ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo::operator!=(const ConfirmBeforeDeletingInfo &other) const
{
    return !operator==(other);
}

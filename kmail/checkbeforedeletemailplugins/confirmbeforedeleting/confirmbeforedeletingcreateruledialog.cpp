/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingcreateruledialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

ConfirmBeforeDeletingCreateRuleDialog::ConfirmBeforeDeletingCreateRuleDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Rule"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    //    mConfirmBeforeDeletingWidget->setObjectName(QStringLiteral("mConfirmBeforeDeletingWidget"));
    //    mainLayout->addWidget(mConfirmBeforeDeletingWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfirmBeforeDeletingCreateRuleDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfirmBeforeDeletingCreateRuleDialog::reject);
}

ConfirmBeforeDeletingCreateRuleDialog::~ConfirmBeforeDeletingCreateRuleDialog()
{
}

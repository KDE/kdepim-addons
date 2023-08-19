/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterdialog.h"
#include "adblockfilterwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

AdblockFilterDialog::AdblockFilterDialog(QWidget *parent)
    : QDialog(parent)
    , mAdblockFilterWidget(new AdblockFilterWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Adblock List"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mAdblockFilterWidget->setObjectName(QStringLiteral("mAdblockFilterWidget"));
    mainLayout->addWidget(mAdblockFilterWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdblockFilterDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdblockFilterDialog::reject);
}

AdblockFilterDialog::~AdblockFilterDialog() = default;

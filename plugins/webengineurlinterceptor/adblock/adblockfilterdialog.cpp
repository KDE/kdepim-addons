/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

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
    setWindowTitle(i18nc("@title:window", "Configure Adblock List"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    mAdblockFilterWidget->setObjectName(QLatin1StringView("mAdblockFilterWidget"));
    mainLayout->addWidget(mAdblockFilterWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdblockFilterDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdblockFilterDialog::reject);
}

AdblockFilterDialog::~AdblockFilterDialog() = default;

void AdblockFilterDialog::loadSettings()
{
    mAdblockFilterWidget->loadSettings();
}

#include "moc_adblockfilterdialog.cpp"

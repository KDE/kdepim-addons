/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterdialog.h"
#include "adblockviewfilterwidget.h"

#include <KLocalizedString>

#include <QDialogButtonBox>
#include <QVBoxLayout>

AdblockViewFilterDialog::AdblockViewFilterDialog(QWidget *parent)
    : QDialog(parent)
    , mAdblockViewFilterWidget(new AdblockViewFilterWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Adblock List"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    mAdblockViewFilterWidget->setObjectName(QLatin1StringView("mAdblockViewFilterWidget"));
    mainLayout->addWidget(mAdblockViewFilterWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdblockViewFilterDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdblockViewFilterDialog::reject);
}

AdblockViewFilterDialog::~AdblockViewFilterDialog() = default;

#include "moc_adblockviewfilterdialog.cpp"
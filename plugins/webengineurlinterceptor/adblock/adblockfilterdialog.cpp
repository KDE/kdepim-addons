/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterdialog.h"
#include "adblockfilterwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

#include <KConfigGroup>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;

namespace
{
static const char myAdblockFilterDialogGroupName[] = "AdblockFilterDialog";
}
AdblockFilterDialog::AdblockFilterDialog(QWidget *parent)
    : QDialog(parent)
    , mAdblockFilterWidget(new AdblockFilterWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Adblock List"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);

    mAdblockFilterWidget->setObjectName("mAdblockFilterWidget"_L1);
    mainLayout->addWidget(mAdblockFilterWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonBox"_L1);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdblockFilterDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdblockFilterDialog::reject);
    readConfig();
}

AdblockFilterDialog::~AdblockFilterDialog()
{
    writeConfig();
}

void AdblockFilterDialog::loadSettings()
{
    mAdblockFilterWidget->loadSettings();
}

void AdblockFilterDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myAdblockFilterDialogGroupName), 600, 400);
}

void AdblockFilterDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAdblockFilterDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

#include "moc_adblockfilterdialog.cpp"

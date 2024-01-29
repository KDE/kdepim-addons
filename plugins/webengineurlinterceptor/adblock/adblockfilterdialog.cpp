/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

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
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    mAdblockFilterWidget->setObjectName(QLatin1StringView("mAdblockFilterWidget"));
    mainLayout->addWidget(mAdblockFilterWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
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
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAdblockFilterDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void AdblockFilterDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAdblockFilterDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

#include "moc_adblockfilterdialog.cpp"

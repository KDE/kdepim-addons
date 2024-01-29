/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterdialog.h"
#include "adblockviewfilterwidget.h"
#include "kwindowconfig.h"

#include <KLocalizedString>

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myAdblockViewFilterDialogGroupName[] = "AdblockViewFilterDialog";
}
AdblockViewFilterDialog::AdblockViewFilterDialog(QWidget *parent)
    : QDialog(parent)
    , mAdblockViewFilterWidget(new AdblockViewFilterWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Show Adblock List"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    mAdblockViewFilterWidget->setObjectName(QLatin1StringView("mAdblockViewFilterWidget"));
    mainLayout->addWidget(mAdblockViewFilterWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdblockViewFilterDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdblockViewFilterDialog::reject);
    readConfig();
}

AdblockViewFilterDialog::~AdblockViewFilterDialog()
{
    writeConfig();
}

void AdblockViewFilterDialog::setFilterText(const QString &str)
{
    mAdblockViewFilterWidget->setFilterText(str);
}

void AdblockViewFilterDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAdblockViewFilterDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void AdblockViewFilterDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAdblockViewFilterDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}
#include "moc_adblockviewfilterdialog.cpp"

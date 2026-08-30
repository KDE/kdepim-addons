/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

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
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;

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
    mainLayout->setObjectName("mainLayout"_L1);

    mAdblockViewFilterWidget->setObjectName("mAdblockViewFilterWidget"_L1);
    mainLayout->addWidget(mAdblockViewFilterWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName("buttonBox"_L1);
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
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myAdblockViewFilterDialogGroupName), 600, 400);
}

void AdblockViewFilterDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAdblockViewFilterDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}
#include "moc_adblockviewfilterdialog.cpp"

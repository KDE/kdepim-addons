/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguredialog.h"
#include "dkimconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
namespace
{
const char myConfigGroupName[] = "DKIMConfigureDialog";
}

DKIMConfigureDialog::DKIMConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mConfigureWidget(new DKIMConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure DKIM"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);

    mConfigureWidget->setObjectName("mConfigureWidget"_L1);
    mainLayout->addWidget(mConfigureWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
    buttonBox->setObjectName("buttonBox"_L1);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DKIMConfigureDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DKIMConfigureDialog::reject);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &DKIMConfigureDialog::slotReset);
    mConfigureWidget->loadSettings();
    readConfig();
}

DKIMConfigureDialog::~DKIMConfigureDialog()
{
    writeConfig();
}

void DKIMConfigureDialog::slotAccepted()
{
    mConfigureWidget->saveSettings();
    accept();
}

void DKIMConfigureDialog::slotReset()
{
    mConfigureWidget->resetSettings();
}

void DKIMConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myConfigGroupName), 600, 400);
}

void DKIMConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

#include "moc_dkimconfiguredialog.cpp"

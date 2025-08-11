/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

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
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    mConfigureWidget->setObjectName(QLatin1StringView("mConfigureWidget"));
    mainLayout->addWidget(mConfigureWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
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
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void DKIMConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

#include "moc_dkimconfiguredialog.cpp"

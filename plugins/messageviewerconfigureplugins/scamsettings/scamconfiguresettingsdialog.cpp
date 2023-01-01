/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingsdialog.h"
#include "scamconfiguresettingswidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myScamConfigureSettingsDialogConfigGroupName[] = "ScamConfigureSettingsDialog";
}
ScamConfigureSettingsDialog::ScamConfigureSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , mScamConfigureSettingsWidget(new ScamConfigureSettingsWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    setWindowTitle(i18nc("@title:window", "Configure Scam Settings"));

    mScamConfigureSettingsWidget->setObjectName(QStringLiteral("mScamConfigureSettingsWidget"));
    mainLayout->addWidget(mScamConfigureSettingsWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &ScamConfigureSettingsDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ScamConfigureSettingsDialog::reject);
    mScamConfigureSettingsWidget->loadSettings();

    readConfig();
}

ScamConfigureSettingsDialog::~ScamConfigureSettingsDialog()
{
    writeConfig();
}

void ScamConfigureSettingsDialog::slotAccepted()
{
    mScamConfigureSettingsWidget->saveSettings();
    accept();
}

void ScamConfigureSettingsDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), myScamConfigureSettingsDialogConfigGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void ScamConfigureSettingsDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), myScamConfigureSettingsDialogConfigGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

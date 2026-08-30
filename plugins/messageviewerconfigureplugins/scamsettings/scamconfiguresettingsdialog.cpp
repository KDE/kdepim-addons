/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

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
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
namespace
{
static const char myScamConfigureSettingsDialogConfigGroupName[] = "ScamConfigureSettingsDialog";
}
ScamConfigureSettingsDialog::ScamConfigureSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , mScamConfigureSettingsWidget(new ScamConfigureSettingsWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    setWindowTitle(i18nc("@title:window", "Configure Scam Settings"));

    mScamConfigureSettingsWidget->setObjectName("mScamConfigureSettingsWidget"_L1);
    mainLayout->addWidget(mScamConfigureSettingsWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonBox"_L1);
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
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myScamConfigureSettingsDialogConfigGroupName), 300, 200);
}

void ScamConfigureSettingsDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myScamConfigureSettingsDialogConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_scamconfiguresettingsdialog.cpp"

/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingsdialog.h"
#include "scamconfiguresettingswidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>

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
    readConfig();
}

ScamConfigureSettingsDialog::~ScamConfigureSettingsDialog()
{
    writeConfig();
}

void ScamConfigureSettingsDialog::readConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), myScamConfigureSettingsDialogConfigGroupName);
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void ScamConfigureSettingsDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), myScamConfigureSettingsDialogConfigGroupName);
    grp.writeEntry("Size", size());
    grp.sync();
}

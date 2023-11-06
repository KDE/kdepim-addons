/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsdialog.h"
#include "folderconfiguresettingswidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigGroupName[] = "FolderConfigureSettingsDialog";
}

FolderConfigureSettingsDialog::FolderConfigureSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , mFolderConfigureSettingsWidget(new FolderConfigureSettingsWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    setWindowTitle(i18nc("@title:window", "Configure Folder Settings"));

    mFolderConfigureSettingsWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsWidget"));
    mainLayout->addWidget(mFolderConfigureSettingsWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::rejected, this, &FolderConfigureSettingsDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &FolderConfigureSettingsDialog::slotSave);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

FolderConfigureSettingsDialog::~FolderConfigureSettingsDialog()
{
    writeConfig();
}

void FolderConfigureSettingsDialog::slotSave()
{
    mFolderConfigureSettingsWidget->save();
    accept();
}

void FolderConfigureSettingsDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void FolderConfigureSettingsDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1String(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_folderconfiguresettingsdialog.cpp"

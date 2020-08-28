/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsdialog.h"
#include "folderconfiguresettingswidget.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

namespace {
static const char myConfigGroupName[] = "FolderConfigureSettingsDialog";
}

FolderConfigureSettingsDialog::FolderConfigureSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    setWindowTitle(i18nc("@title:window", "Configure Folder Settings"));

    mFolderConfigureSettingsWidget = new FolderConfigureSettingsWidget(this);
    mFolderConfigureSettingsWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsWidget"));
    mainLayout->addWidget(mFolderConfigureSettingsWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Ok, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::rejected, this, &FolderConfigureSettingsDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &FolderConfigureSettingsDialog::accept);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

FolderConfigureSettingsDialog::~FolderConfigureSettingsDialog()
{
    writeConfig();
}

void FolderConfigureSettingsDialog::readConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void FolderConfigureSettingsDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    grp.writeEntry("Size", size());
    grp.sync();
}

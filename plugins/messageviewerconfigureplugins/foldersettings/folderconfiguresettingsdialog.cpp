/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
#if 0
#endif
}

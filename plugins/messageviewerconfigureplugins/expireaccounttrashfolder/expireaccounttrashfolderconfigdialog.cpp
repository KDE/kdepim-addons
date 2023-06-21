/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "expireaccounttrashfolderconfigdialog.h"
#include "expireaccounttrashfolderconfigwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigGroupName[] = "ExpireAccountTrashFolderConfigDialog";
}

ExpireAccountTrashFolderConfigDialog::ExpireAccountTrashFolderConfigDialog(QWidget *parent)
    : QDialog(parent)
    , mExpireAccountTrashFolderConfig(new ExpireAccountTrashFolderConfigWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    setWindowTitle(i18nc("@title:window", "Configure Expiry Account Trash Folder"));

    mExpireAccountTrashFolderConfig->setObjectName(QStringLiteral("mExpireAccountTrashFolderConfig"));
    mainLayout->addWidget(mExpireAccountTrashFolderConfig);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ExpireAccountTrashFolderConfigDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ExpireAccountTrashFolderConfigDialog::accept);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

ExpireAccountTrashFolderConfigDialog::~ExpireAccountTrashFolderConfigDialog()
{
    mExpireAccountTrashFolderConfig->save();
    writeConfig();
}

void ExpireAccountTrashFolderConfigDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void ExpireAccountTrashFolderConfigDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_expireaccounttrashfolderconfigdialog.cpp"

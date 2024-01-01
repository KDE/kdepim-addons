/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

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
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    setWindowTitle(i18nc("@title:window", "Configure Expiry Account Trash Folder"));

    mExpireAccountTrashFolderConfig->setObjectName(QLatin1StringView("mExpireAccountTrashFolderConfig"));
    mainLayout->addWidget(mExpireAccountTrashFolderConfig);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    buttonBox->setObjectName(QLatin1StringView("buttonbox"));
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
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void ExpireAccountTrashFolderConfigDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1String(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_expireaccounttrashfolderconfigdialog.cpp"

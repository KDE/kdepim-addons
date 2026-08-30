/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

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
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
namespace
{
const char myConfigGroupName[] = "ExpireAccountTrashFolderConfigDialog";
}

ExpireAccountTrashFolderConfigDialog::ExpireAccountTrashFolderConfigDialog(QWidget *parent)
    : QDialog(parent)
    , mExpireAccountTrashFolderConfig(new ExpireAccountTrashFolderConfigWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    setWindowTitle(i18nc("@title:window", "Configure Expiry Account Trash Folder"));

    mExpireAccountTrashFolderConfig->setObjectName("mExpireAccountTrashFolderConfig"_L1);
    mainLayout->addWidget(mExpireAccountTrashFolderConfig);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    buttonBox->setObjectName("buttonbox"_L1);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ExpireAccountTrashFolderConfigDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ExpireAccountTrashFolderConfigDialog::slotAccepted);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

ExpireAccountTrashFolderConfigDialog::~ExpireAccountTrashFolderConfigDialog()
{
    writeConfig();
}

void ExpireAccountTrashFolderConfigDialog::slotAccepted()
{
    mExpireAccountTrashFolderConfig->save();
    accept();
}

void ExpireAccountTrashFolderConfigDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myConfigGroupName), 300, 200);
}

void ExpireAccountTrashFolderConfigDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_expireaccounttrashfolderconfigdialog.cpp"

/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "expireaccounttrashfolderconfigdialog.h"
#include "expireaccounttrashfolderconfigwidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <KSharedConfig>

namespace {
static const char myConfigGroupName[] = "ExpireAccountTrashFolderConfigDialog";
}

ExpireAccountTrashFolderConfigDialog::ExpireAccountTrashFolderConfigDialog(QWidget *parent)
    : QDialog(parent)
    , mExpireAccountTrashFolderConfig(new ExpireAccountTrashFolderConfigWidget(this))
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    setWindowTitle(i18nc("@title:window", "Configure Expiry Account Trash Folder"));

    mExpireAccountTrashFolderConfig->setObjectName(QStringLiteral("mExpireAccountTrashFolderConfig"));
    mainLayout->addWidget(mExpireAccountTrashFolderConfig);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Ok, this);
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
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void ExpireAccountTrashFolderConfigDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    grp.writeEntry("Size", size());
    grp.sync();
}

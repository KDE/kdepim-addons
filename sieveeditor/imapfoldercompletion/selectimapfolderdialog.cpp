/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderdialog.h"
#include "selectimapfolderwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

SelectImapFolderDialog::SelectImapFolderDialog(const KSieveUi::SieveImapAccountSettings &account, QWidget *parent)
    : QDialog(parent)
    , mSelectImapFolderWidget(new SelectImapFolderWidget(account, this))
    , mNewFolder(new QPushButton(i18n("Create Folder..."), this))
{
    setWindowTitle(i18nc("@title:window", "Select IMAP folder"));
    auto layout = new QVBoxLayout(this);

    mSelectImapFolderWidget->setObjectName(QStringLiteral("selectimapfolderwidget"));
    layout->addWidget(mSelectImapFolderWidget);
    connect(mSelectImapFolderWidget, &SelectImapFolderWidget::folderSelected, this, &SelectImapFolderDialog::accept);
    connect(mSelectImapFolderWidget, &SelectImapFolderWidget::folderIsSelected, this, &SelectImapFolderDialog::slotEnabledNewFolder);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttonBox);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));

    mNewFolder->setObjectName(QStringLiteral("createfolder"));
    mNewFolder->setEnabled(false);
    buttonBox->addButton(mNewFolder, QDialogButtonBox::ActionRole);
    connect(mNewFolder, &QPushButton::clicked, this, &SelectImapFolderDialog::slotCreateFolder);

    // Set the button actions
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SelectImapFolderDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SelectImapFolderDialog::reject);
    readConfig();
}

SelectImapFolderDialog::~SelectImapFolderDialog()
{
    writeConfig();
}

QString SelectImapFolderDialog::selectedFolderName() const
{
    return mSelectImapFolderWidget->selectedFolderName();
}

void SelectImapFolderDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "SelectImapFolderDialog");
    group.writeEntry("Size", size());
}

void SelectImapFolderDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "SelectImapFolderDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void SelectImapFolderDialog::slotCreateFolder()
{
    mSelectImapFolderWidget->createFolder();
}

void SelectImapFolderDialog::slotEnabledNewFolder(bool enabled)
{
    mNewFolder->setEnabled(enabled);
}

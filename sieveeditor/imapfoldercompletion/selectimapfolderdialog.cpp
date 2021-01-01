/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderdialog.h"
#include "selectimapfolderwidget.h"

#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>

SelectImapFolderDialog::SelectImapFolderDialog(const KSieveUi::SieveImapAccountSettings &account, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Select IMAP folder"));
    auto *layout = new QVBoxLayout(this);

    mSelectImapFolderWidget = new SelectImapFolderWidget(account, this);
    mSelectImapFolderWidget->setObjectName(QStringLiteral("selectimapfolderwidget"));
    layout->addWidget(mSelectImapFolderWidget);
    connect(mSelectImapFolderWidget, &SelectImapFolderWidget::folderSelected, this, &SelectImapFolderDialog::accept);
    connect(mSelectImapFolderWidget, &SelectImapFolderWidget::folderIsSelected, this, &SelectImapFolderDialog::slotEnabledNewFolder);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttonBox);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));

    mNewFolder = new QPushButton(i18n("Create Folder..."), this);
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
    KConfigGroup group(KSharedConfig::openConfig(), "SelectImapFolderDialog");
    group.writeEntry("Size", size());
}

void SelectImapFolderDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "SelectImapFolderDialog");
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

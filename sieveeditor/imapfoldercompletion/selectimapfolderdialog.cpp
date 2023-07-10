/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderdialog.h"
#include "selectimapfolderwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>

#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigSelectImapFolderDialog[] = "SelectImapFolderDialog";
}

SelectImapFolderDialog::SelectImapFolderDialog(const KSieveCore::SieveImapAccountSettings &account, QWidget *parent)
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

void SelectImapFolderDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigSelectImapFolderDialog);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void SelectImapFolderDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigSelectImapFolderDialog);
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

void SelectImapFolderDialog::slotCreateFolder()
{
    mSelectImapFolderWidget->createFolder();
}

void SelectImapFolderDialog::slotEnabledNewFolder(bool enabled)
{
    mNewFolder->setEnabled(enabled);
}

#include "moc_selectimapfolderdialog.cpp"

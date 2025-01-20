/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugindialog.h"
#include "checkfoldersizeaccountpluginwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

CheckFolderSizeAccountPluginDialog::CheckFolderSizeAccountPluginDialog(QWidget *parent)
    : QDialog(parent)
    , mCheckFolderSizeAccountPluginWidget(new CheckFolderSizeAccountPluginWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    setWindowTitle(i18nc("@title:window", "Check Folder Size"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckFolderSizeAccountPluginDialog::reject);

    mCheckFolderSizeAccountPluginWidget->setObjectName(QLatin1StringView("mCheckFolderSizeAccountPluginWidget"));
    mainLayout->addWidget(mCheckFolderSizeAccountPluginWidget);
    mainLayout->addWidget(buttonBox);
}

CheckFolderSizeAccountPluginDialog::~CheckFolderSizeAccountPluginDialog() = default;

#include "moc_checkfoldersizeaccountplugindialog.cpp"

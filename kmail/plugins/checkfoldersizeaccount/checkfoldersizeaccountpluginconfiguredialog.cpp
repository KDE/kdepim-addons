/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccountpluginconfiguredialog.h"
#include "checkfoldersizeaccountpluginconfigurewidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountPluginConfigureDialog::CheckFolderSizeAccountPluginConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mCheckFolderSizeAccountPluginConfigureWidget(new CheckFolderSizeAccountPluginConfigureWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    setWindowTitle(i18nc("@title:window", "Check Folder Size"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckFolderSizeAccountPluginConfigureDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CheckFolderSizeAccountPluginConfigureDialog::accept);

    mCheckFolderSizeAccountPluginConfigureWidget->setObjectName(QLatin1StringView("mCheckFolderSizeAccountPluginConfigureWidget"));
    mainLayout->addWidget(mCheckFolderSizeAccountPluginConfigureWidget);
    mainLayout->addWidget(buttonBox);
}

CheckFolderSizeAccountPluginConfigureDialog::~CheckFolderSizeAccountPluginConfigureDialog() = default;

#include "moc_checkfoldersizeaccountpluginconfiguredialog.cpp"

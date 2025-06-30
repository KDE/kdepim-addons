/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccountpluginconfiguredialog.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountPluginConfigureDialog::CheckFolderSizeAccountPluginConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    setWindowTitle(i18nc("@title:window", "Check Folder Size"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    /*
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckFolderSizeAccountPluginDialog::reject);

    mCheckFolderSizeAccountPluginWidget->setObjectName(QLatin1StringView("mCheckFolderSizeAccountPluginWidget"));
    mainLayout->addWidget(mCheckFolderSizeAccountPluginWidget);
    */
    mainLayout->addWidget(buttonBox);
}

CheckFolderSizeAccountPluginConfigureDialog::~CheckFolderSizeAccountPluginConfigureDialog() = default;

#include "moc_checkfoldersizeaccountpluginconfiguredialog.cpp"

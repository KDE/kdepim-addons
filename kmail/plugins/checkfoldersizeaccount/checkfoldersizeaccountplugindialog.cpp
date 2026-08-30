/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugindialog.h"

#include "checkfoldersizeaccountpluginwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myConfigGroupName[] = "CheckFolderSizeAccountPluginDialog";
}

using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountPluginDialog::CheckFolderSizeAccountPluginDialog(QWidget *parent)
    : QDialog(parent)
    , mCheckFolderSizeAccountPluginWidget(new CheckFolderSizeAccountPluginWidget(this))
{
    setAttribute(Qt::WA_DeleteOnClose);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    setWindowTitle(i18nc("@title:window", "Check Folder Size"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckFolderSizeAccountPluginDialog::reject);

    mCheckFolderSizeAccountPluginWidget->setObjectName("mCheckFolderSizeAccountPluginWidget"_L1);
    mainLayout->addWidget(mCheckFolderSizeAccountPluginWidget);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

CheckFolderSizeAccountPluginDialog::~CheckFolderSizeAccountPluginDialog()
{
    writeConfig();
}

void CheckFolderSizeAccountPluginDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void CheckFolderSizeAccountPluginDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myConfigGroupName), 500, 300);
}

#include "moc_checkfoldersizeaccountplugindialog.cpp"

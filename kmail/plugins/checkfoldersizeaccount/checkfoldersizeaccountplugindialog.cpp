/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountplugindialog.h"
using namespace Qt::Literals::StringLiterals;

#include "checkfoldersizeaccountpluginwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigGroupName[] = "CheckFolderSizeAccountPluginDialog";
}

CheckFolderSizeAccountPluginDialog::CheckFolderSizeAccountPluginDialog(QWidget *parent)
    : QDialog(parent)
    , mCheckFolderSizeAccountPluginWidget(new CheckFolderSizeAccountPluginWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    setWindowTitle(i18nc("@title:window", "Check Folder Size"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckFolderSizeAccountPluginDialog::reject);

    mCheckFolderSizeAccountPluginWidget->setObjectName(QLatin1StringView("mCheckFolderSizeAccountPluginWidget"));
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
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

#include "moc_checkfoldersizeaccountplugindialog.cpp"

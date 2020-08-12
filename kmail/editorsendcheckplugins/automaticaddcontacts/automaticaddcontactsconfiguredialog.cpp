/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfiguredialog.h"
#include "automaticaddcontactsconfigurewidget.h"
#include <KLocalizedString>

AutomaticAddContactsConfigureDialog::AutomaticAddContactsConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
    , mConfigureWidget(nullptr)
{
    setWindowTitle(i18nc("@title:window", "Configure \"Automatic Add Contacts\" Plugin"));
    initLayout();
}

AutomaticAddContactsConfigureDialog::~AutomaticAddContactsConfigureDialog()
{
}

QWidget *AutomaticAddContactsConfigureDialog::createLayout()
{
    mConfigureWidget = new AutomaticAddContactsConfigureWidget(this);
    return mConfigureWidget;
}

void AutomaticAddContactsConfigureDialog::save()
{
    mConfigureWidget->saveSettings();
}

void AutomaticAddContactsConfigureDialog::load()
{
    mConfigureWidget->loadSettings();
}

void AutomaticAddContactsConfigureDialog::reset()
{
    mConfigureWidget->resetSettings();
}

void AutomaticAddContactsConfigureDialog::help()
{
    showHelp(QStringLiteral("kmail2"), mConfigureWidget->helpAnchor());
}

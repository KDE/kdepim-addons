/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguredialog.h"
#include "confirmaddressconfigurewidget.h"
#include <KLocalizedString>

ConfirmAddressConfigureDialog::ConfirmAddressConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure \"Confirm Email Address\" Plugin"));
    initLayout();
}

ConfirmAddressConfigureDialog::~ConfirmAddressConfigureDialog() = default;

QWidget *ConfirmAddressConfigureDialog::createLayout()
{
    mConfigureWidget = new ConfirmAddressConfigureWidget(this);
    return mConfigureWidget;
}

void ConfirmAddressConfigureDialog::save()
{
    mConfigureWidget->saveSettings();
}

void ConfirmAddressConfigureDialog::load()
{
    mConfigureWidget->loadSettings();
}

void ConfirmAddressConfigureDialog::reset()
{
    mConfigureWidget->resetSettings();
}

void ConfirmAddressConfigureDialog::help()
{
    showHelp(QStringLiteral("kmail2"), mConfigureWidget->helpAnchor());
}

#include "moc_confirmaddressconfiguredialog.cpp"

/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguredialog.h"

#include "confirmaddressconfigurewidget.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

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
    showHelp(u"kmail2"_s, mConfigureWidget->helpAnchor());
}

#include "moc_confirmaddressconfiguredialog.cpp"

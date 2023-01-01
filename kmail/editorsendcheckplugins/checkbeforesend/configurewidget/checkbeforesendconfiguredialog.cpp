/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendconfiguredialog.h"
#include "checkbeforesendconfigurewidget.h"
#include <KLocalizedString>

CheckBeforeSendConfigureDialog::CheckBeforeSendConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure \"Check Before Send Mail\" Plugin"));
    initLayout();
}

CheckBeforeSendConfigureDialog::~CheckBeforeSendConfigureDialog() = default;

QWidget *CheckBeforeSendConfigureDialog::createLayout()
{
    mConfigureWidget = new CheckBeforeSendConfigureWidget(this);
    return mConfigureWidget;
}

void CheckBeforeSendConfigureDialog::save()
{
    mConfigureWidget->saveSettings();
}

void CheckBeforeSendConfigureDialog::load()
{
    mConfigureWidget->loadSettings();
}

void CheckBeforeSendConfigureDialog::reset()
{
    mConfigureWidget->resetSettings();
}

void CheckBeforeSendConfigureDialog::help()
{
    showHelp(QStringLiteral("kmail2"), mConfigureWidget->helpAnchor());
}

/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptorconfiguredialog.h"
#include "adblockautomaticruleslistwidget.h"
#include "adblockpluginurlinterceptorconfigurewidget.h"

#include <KLocalizedString>

using namespace AdBlock;

AdblockPluginUrlInterceptorConfigureDialog::AdblockPluginUrlInterceptorConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure AdBlock Plugin"));
    initLayout();
}

AdblockPluginUrlInterceptorConfigureDialog::~AdblockPluginUrlInterceptorConfigureDialog()
{
}

QWidget *AdblockPluginUrlInterceptorConfigureDialog::createLayout()
{
    mAdblockConfigureWidget = new AdblockPluginUrlInterceptorConfigureWidget(this);
    return mAdblockConfigureWidget;
}

void AdblockPluginUrlInterceptorConfigureDialog::save()
{
    mAdblockConfigureWidget->saveSettings();
}

void AdblockPluginUrlInterceptorConfigureDialog::load()
{
    mAdblockConfigureWidget->loadSettings();
}

void AdBlock::AdblockPluginUrlInterceptorConfigureDialog::reset()
{
    mAdblockConfigureWidget->resetSettings();
}

void AdBlock::AdblockPluginUrlInterceptorConfigureDialog::help()
{
    // TODO we can use in akregator too. We need a specific doc.
    showHelp(QStringLiteral("kmail2"), mAdblockConfigureWidget->helpAnchor());
}

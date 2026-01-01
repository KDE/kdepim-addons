/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptorconfiguredialog.h"
#include "adblockpluginurlinterceptorconfigurewidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QWindow>

namespace
{
static const char myConfigGroupName[] = "AdblockPluginUrlInterceptorConfigureDialog";
}
AdblockPluginUrlInterceptorConfigureDialog::AdblockPluginUrlInterceptorConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure AdBlock Plugin"));
    initLayout();
    readConfig();
}

AdblockPluginUrlInterceptorConfigureDialog::~AdblockPluginUrlInterceptorConfigureDialog()
{
    writeConfig();
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

void AdblockPluginUrlInterceptorConfigureDialog::reset()
{
    mAdblockConfigureWidget->resetSettings();
}

void AdblockPluginUrlInterceptorConfigureDialog::help()
{
    // TODO we can use in akregator too. We need a specific doc.
    showHelp(QStringLiteral("kmail2"), mAdblockConfigureWidget->helpAnchor());
}

void AdblockPluginUrlInterceptorConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void AdblockPluginUrlInterceptorConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

#include "moc_adblockpluginurlinterceptorconfiguredialog.cpp"

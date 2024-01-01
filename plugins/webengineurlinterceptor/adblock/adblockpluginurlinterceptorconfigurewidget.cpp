/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptorconfigurewidget.h"
#include "adblockfilterwidget.h"
#include "globalsettings_webengineurlinterceptoradblock.h"

#include <KSharedConfig>
#include <QHBoxLayout>

AdblockPluginUrlInterceptorConfigureWidget::AdblockPluginUrlInterceptorConfigureWidget(QWidget *parent)
    : WebEngineViewer::NetworkPluginUrlInterceptorConfigureWidget(parent)
    , mAdblockFilterWidget(new AdblockFilterWidget(this))
{
    auto hbox = new QHBoxLayout(this);
    hbox->setContentsMargins({});
    mAdblockFilterWidget->setObjectName(QLatin1StringView("mAdblockFilterWidget"));
    hbox->addWidget(mAdblockFilterWidget);
    connect(mAdblockFilterWidget, &AdblockFilterWidget::settingsChanged, this, &AdblockPluginUrlInterceptorConfigureWidget::configureChanged);
}

AdblockPluginUrlInterceptorConfigureWidget::~AdblockPluginUrlInterceptorConfigureWidget() = default;

void AdblockPluginUrlInterceptorConfigureWidget::loadSettings()
{
    mAdblockFilterWidget->loadSettings();
}

void AdblockPluginUrlInterceptorConfigureWidget::saveSettings()
{
    mAdblockFilterWidget->saveSettings();
}

void AdblockPluginUrlInterceptorConfigureWidget::resetSettings()
{
    const bool bUseDefaults = AdBlockSettings::self()->useDefaults(true);
    mAdblockFilterWidget->loadSettings();
    AdBlockSettings::self()->useDefaults(bUseDefaults);
}

#include "moc_adblockpluginurlinterceptorconfigurewidget.cpp"

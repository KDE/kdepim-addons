/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptorconfigurewidget.h"
#include "adblockfilterwidget.h"
#include <QHBoxLayout>

AdblockPluginUrlInterceptorConfigureWidget::AdblockPluginUrlInterceptorConfigureWidget(QWidget *parent)
    : WebEngineViewer::NetworkPluginUrlInterceptorConfigureWidget(parent)
    , mAdblockFilterWidget(new AdblockFilterWidget(this))
{
    auto hbox = new QHBoxLayout(this);
    hbox->setContentsMargins({});
    mAdblockFilterWidget->setObjectName(QStringLiteral("mAdblockFilterWidget"));
    hbox->addWidget(mAdblockFilterWidget);
    // connect(mAdblockFilterWidget, &AdBlockSettingWidget::settingsChanged, this, &AdblockPluginUrlInterceptorConfigureWidget::configureChanged);
}

AdblockPluginUrlInterceptorConfigureWidget::~AdblockPluginUrlInterceptorConfigureWidget() = default;

void AdblockPluginUrlInterceptorConfigureWidget::loadSettings()
{
    //    mConfigureWidget->doLoadFromGlobalSettings();
}

void AdblockPluginUrlInterceptorConfigureWidget::saveSettings()
{
    //    mConfigureWidget->save();
    Q_EMIT configureChanged();
}

void AdblockPluginUrlInterceptorConfigureWidget::resetSettings()
{
    //    mConfigureWidget->doResetToDefaultsOther();
}

#include "moc_adblockpluginurlinterceptorconfigurewidget.cpp"

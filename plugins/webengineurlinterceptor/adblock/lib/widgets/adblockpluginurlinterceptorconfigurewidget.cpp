/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptorconfigurewidget.h"
#include "adblocksettingwidget.h"
#include <QHBoxLayout>

using namespace AdBlock;

AdblockPluginUrlInterceptorConfigureWidget::AdblockPluginUrlInterceptorConfigureWidget(QWidget *parent)
    : WebEngineViewer::NetworkPluginUrlInterceptorConfigureWidget(parent)
{
    auto hbox = new QHBoxLayout(this);
    hbox->setContentsMargins({});
    mConfigureWidget = new AdBlock::AdBlockSettingWidget(this);
    mConfigureWidget->setObjectName(QStringLiteral("configurewidget"));
    hbox->addWidget(mConfigureWidget);
    connect(mConfigureWidget, &AdBlockSettingWidget::settingsChanged, this, &AdblockPluginUrlInterceptorConfigureWidget::configureChanged);
}

AdblockPluginUrlInterceptorConfigureWidget::~AdblockPluginUrlInterceptorConfigureWidget()
{
}

void AdblockPluginUrlInterceptorConfigureWidget::loadSettings()
{
    mConfigureWidget->doLoadFromGlobalSettings();
}

void AdblockPluginUrlInterceptorConfigureWidget::saveSettings()
{
    mConfigureWidget->save();
    Q_EMIT configureChanged();
}

void AdblockPluginUrlInterceptorConfigureWidget::resetSettings()
{
    mConfigureWidget->doResetToDefaultsOther();
}

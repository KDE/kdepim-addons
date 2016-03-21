/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "adblockpluginurlinterceptor.h"
#include "adblockinterceptorinterface.h"
#include "adblockpluginurlinterceptorconfigurewidget.h"
#include "lib/adblockmanager.h"
#include <MessageViewer/NetworkPluginUrlInterceptorInterface>
#include <kpluginfactory.h>

K_PLUGIN_FACTORY_WITH_JSON(AdblockPluginUrlInterceptorFactory, "messageviewer_adblockurlinterceptor.json", registerPlugin<AdblockPluginUrlInterceptor>();)
AdblockPluginUrlInterceptor::AdblockPluginUrlInterceptor(QObject *parent, const QList<QVariant> &)
    : MessageViewer::NetworkPluginUrlInterceptor(parent)
{
}

AdblockPluginUrlInterceptor::~AdblockPluginUrlInterceptor()
{

}

MessageViewer::NetworkPluginUrlInterceptorInterface *AdblockPluginUrlInterceptor::createInterface(QWebEngineView *webEngine, QObject *parent)
{
    return new AdblockInterceptorInterface(parent);
}

bool AdblockPluginUrlInterceptor::hasConfigureSupport() const
{
    return true;
}

MessageViewer::NetworkPluginUrlInterceptorConfigureWidget *AdblockPluginUrlInterceptor::createConfigureWidget(QWidget *parent)
{
    AdblockPluginUrlInterceptorConfigureWidget *configureWidget = new AdblockPluginUrlInterceptorConfigureWidget(parent);
    connect(configureWidget, &AdblockPluginUrlInterceptorConfigureWidget::configChanged, AdBlock::AdblockManager::self(), &AdBlock::AdblockManager::reloadConfig);
    return configureWidget;
}


#include "adblockpluginurlinterceptor.moc"

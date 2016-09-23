/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "adblockpluginurlinterceptor.h"
#include "adblockinterceptorinterface.h"
#include "../lib/widgets/adblockpluginurlinterceptorconfigurewidget.h"
#include "lib/adblockmanager.h"
#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>
#include <kpluginfactory.h>
#include <KLocalizedString>

K_PLUGIN_FACTORY_WITH_JSON(AdblockPluginUrlInterceptorFactory, "messageviewer_adblockurlinterceptor.json", registerPlugin<AdblockPluginUrlInterceptor>();)
AdblockPluginUrlInterceptor::AdblockPluginUrlInterceptor(QObject *parent, const QList<QVariant> &)
    : WebEngineViewer::NetworkPluginUrlInterceptor(parent)
{
}

AdblockPluginUrlInterceptor::~AdblockPluginUrlInterceptor()
{

}

WebEngineViewer::NetworkPluginUrlInterceptorInterface *AdblockPluginUrlInterceptor::createInterface(QWebEngineView *webEngine, QObject *parent)
{
    AdblockInterceptorInterface *adblockInterface = new AdblockInterceptorInterface(parent);
    adblockInterface->setWebEngineView(webEngine);
    return adblockInterface;
}

bool AdblockPluginUrlInterceptor::hasConfigureDialog() const
{
    return true;
}

WebEngineViewer::NetworkPluginUrlInterceptorConfigureWidgetSetting AdblockPluginUrlInterceptor::createConfigureWidget(QWidget *parent)
{
    WebEngineViewer::NetworkPluginUrlInterceptorConfigureWidgetSetting settings;
    settings.name = i18n("AdBlock");

    AdBlock::AdblockPluginUrlInterceptorConfigureWidget *configureWidget = new AdBlock::AdblockPluginUrlInterceptorConfigureWidget(parent);
    settings.configureWidget = configureWidget;
    return settings;
}
void AdblockPluginUrlInterceptor::showConfigureDialog(QWidget *parent)
{
    //TODO
}

#include "adblockpluginurlinterceptor.moc"



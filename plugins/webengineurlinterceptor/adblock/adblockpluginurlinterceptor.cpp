/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptor.h"
#include "../lib/widgets/adblockpluginurlinterceptorconfiguredialog.h"
#include "../lib/widgets/adblockpluginurlinterceptorconfigurewidget.h"
#include "adblockinterceptorinterface.h"
#include "lib/adblockmanager.h"
#include <KPluginFactory>
#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>

K_PLUGIN_CLASS_WITH_JSON(AdblockPluginUrlInterceptor, "messageviewer_adblockurlinterceptor.json")
AdblockPluginUrlInterceptor::AdblockPluginUrlInterceptor(QObject *parent, const QList<QVariant> &)
    : WebEngineViewer::NetworkPluginUrlInterceptor(parent)
{
}

AdblockPluginUrlInterceptor::~AdblockPluginUrlInterceptor() = default;

WebEngineViewer::NetworkPluginUrlInterceptorInterface *AdblockPluginUrlInterceptor::createInterface(QWebEngineView *webEngine, QObject *parent)
{
    auto adblockInterface = new AdblockInterceptorInterface(parent);
    adblockInterface->setWebEngineView(webEngine);
    return adblockInterface;
}

bool AdblockPluginUrlInterceptor::hasConfigureDialog() const
{
    return true;
}

void AdblockPluginUrlInterceptor::showConfigureDialog(QWidget *parent)
{
    AdBlock::AdblockPluginUrlInterceptorConfigureDialog dlg(parent);
    dlg.exec();
}

#include "adblockpluginurlinterceptor.moc"

/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptor.h"
#include "adblockinterceptorinterface.h"
#include "../lib/widgets/adblockpluginurlinterceptorconfigurewidget.h"
#include "lib/adblockmanager.h"
#include "../lib/widgets/adblockpluginurlinterceptorconfiguredialog.h"
#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AdblockPluginUrlInterceptor, "messageviewer_adblockurlinterceptor.json")
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

void AdblockPluginUrlInterceptor::showConfigureDialog(QWidget *parent)
{
    QPointer<AdBlock::AdblockPluginUrlInterceptorConfigureDialog> dlg = new AdBlock::AdblockPluginUrlInterceptorConfigureDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "adblockpluginurlinterceptor.moc"

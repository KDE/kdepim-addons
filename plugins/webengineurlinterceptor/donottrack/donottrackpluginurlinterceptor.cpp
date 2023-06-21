/*
    SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "donottrackpluginurlinterceptor.h"
#include "donottrackinterceptorinterface.h"
#include <KPluginFactory>
#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>

K_PLUGIN_CLASS_WITH_JSON(DoNotTrackPluginUrlInterceptor, "messageviewer_donottrackurlinterceptor.json")
DoNotTrackPluginUrlInterceptor::DoNotTrackPluginUrlInterceptor(QObject *parent, const QList<QVariant> &)
    : WebEngineViewer::NetworkPluginUrlInterceptor(parent)
{
}

DoNotTrackPluginUrlInterceptor::~DoNotTrackPluginUrlInterceptor() = default;

WebEngineViewer::NetworkPluginUrlInterceptorInterface *DoNotTrackPluginUrlInterceptor::createInterface(QWebEngineView *webEngine, QObject *parent)
{
    Q_UNUSED(webEngine)
    return new DoNotTrackInterceptorInterface(parent);
}

#include "donottrackpluginurlinterceptor.moc"

#include "moc_donottrackpluginurlinterceptor.cpp"

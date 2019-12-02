/*
    Copyright (c) 2016-2019 Montel Laurent <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "donottrackpluginurlinterceptor.h"
#include "donottrackinterceptorinterface.h"
#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(DoNotTrackPluginUrlInterceptor, "messageviewer_donottrackurlinterceptor.json")
DoNotTrackPluginUrlInterceptor::DoNotTrackPluginUrlInterceptor(QObject *parent, const QList<QVariant> &)
    : WebEngineViewer::NetworkPluginUrlInterceptor(parent)
{
}

DoNotTrackPluginUrlInterceptor::~DoNotTrackPluginUrlInterceptor()
{
}

WebEngineViewer::NetworkPluginUrlInterceptorInterface *DoNotTrackPluginUrlInterceptor::createInterface(QWebEngineView *webEngine, QObject *parent)
{
    Q_UNUSED(webEngine);
    return new DoNotTrackInterceptorInterface(parent);
}

#include "donottrackpluginurlinterceptor.moc"

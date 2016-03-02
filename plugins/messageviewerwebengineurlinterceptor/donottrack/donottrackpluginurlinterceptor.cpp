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

#include "donottrackpluginurlinterceptor.h"
#include "donottrackinterceptorinterface.h"
#include <MessageViewer/NetworkPluginUrlInterceptorInterface>
#include <kpluginfactory.h>
#include <QDebug>

K_PLUGIN_FACTORY_WITH_JSON(DoNotTrackPluginUrlInterceptorFactory, "messageviewer_donottrackurlinterceptor.json", registerPlugin<DoNotTrackPluginUrlInterceptor>();)
DoNotTrackPluginUrlInterceptor::DoNotTrackPluginUrlInterceptor(QObject *parent, const QList<QVariant> &)
    : MessageViewer::NetworkPluginUrlInterceptor(parent)
{
    qDebug() << " DoNotTrackPluginUrlInterceptor::DoNotTrackPluginUrlInterceptor(QObject *parent, const QList<QVariant> &)" << this;
}

DoNotTrackPluginUrlInterceptor::~DoNotTrackPluginUrlInterceptor()
{

}

MessageViewer::NetworkPluginUrlInterceptorInterface *DoNotTrackPluginUrlInterceptor::createInterface(QObject *parent)
{
    return new DoNotTrackInterceptorInterface(parent);
}

#include "donottrackpluginurlinterceptor.moc"

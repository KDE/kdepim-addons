/*
    Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

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

#ifndef DONOTTRACKPLUGINURLINTERCEPTOR_H
#define DONOTTRACKPLUGINURLINTERCEPTOR_H

#include <WebEngineViewer/NetworkPluginUrlInterceptor>
#include <QVariant>
namespace WebEngineViewer {
class NetworkPluginUrlInterceptorInterface;
}
class DoNotTrackPluginUrlInterceptor : public WebEngineViewer::NetworkPluginUrlInterceptor
{
    Q_OBJECT
public:
    explicit DoNotTrackPluginUrlInterceptor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~DoNotTrackPluginUrlInterceptor() override;

    WebEngineViewer::NetworkPluginUrlInterceptorInterface *createInterface(QWebEngineView *webEngine, QObject *parent) override;
};

#endif // DONOTTRACKPLUGINURLINTERCEPTOR_H

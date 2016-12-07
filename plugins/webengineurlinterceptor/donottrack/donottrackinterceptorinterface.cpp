/*
    Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#include "donottrackinterceptorinterface.h"
#include <QtWebEngineCore/qwebengineurlrequestinfo.h>
#include "donottracksettings.h"

DoNotTrackInterceptorInterface::DoNotTrackInterceptorInterface(QObject *parent)
    : WebEngineViewer::NetworkPluginUrlInterceptorInterface(parent)
{
}

DoNotTrackInterceptorInterface::~DoNotTrackInterceptorInterface()
{

}

bool DoNotTrackInterceptorInterface::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if (DoNotTrackSettings::doNotTrack()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 8, 0)
        //Laurent Comment it for the moment workaround a bug for QtWebEngine
        info.setHttpHeader(QByteArrayLiteral("DNT"), QByteArrayLiteral("1"));
#endif
    }
    return false;
}

/*
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
        info.setHttpHeader(QByteArrayLiteral("DNT"), QByteArrayLiteral("1"));
    }
    return false;
}

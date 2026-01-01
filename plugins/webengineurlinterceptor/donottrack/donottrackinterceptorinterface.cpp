/*
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "donottrackinterceptorinterface.h"
#include "donottracksettings.h"
#include <QtWebEngineCore/qwebengineurlrequestinfo.h>

DoNotTrackInterceptorInterface::DoNotTrackInterceptorInterface(QObject *parent)
    : WebEngineViewer::NetworkPluginUrlInterceptorInterface(parent)
{
}

DoNotTrackInterceptorInterface::~DoNotTrackInterceptorInterface() = default;

bool DoNotTrackInterceptorInterface::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if (DoNotTrackSettings::doNotTrack()) {
        info.setHttpHeader(QByteArrayLiteral("DNT"), QByteArrayLiteral("1"));
    }
    return false;
}

#include "moc_donottrackinterceptorinterface.cpp"

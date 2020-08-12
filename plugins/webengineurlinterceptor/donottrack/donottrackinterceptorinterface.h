/*
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DONOTTRACKINTERCEPTORINTERFACE_H
#define DONOTTRACKINTERCEPTORINTERFACE_H

#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>
class DoNotTrackInterceptorInterface : public WebEngineViewer::NetworkPluginUrlInterceptorInterface
{
    Q_OBJECT
public:
    explicit DoNotTrackInterceptorInterface(QObject *parent = nullptr);
    ~DoNotTrackInterceptorInterface() override;

    bool interceptRequest(QWebEngineUrlRequestInfo &info) override;
};

#endif // DONOTTRACKINTERCEPTORINTERFACE_H

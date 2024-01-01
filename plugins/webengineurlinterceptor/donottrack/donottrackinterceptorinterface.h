/*
    SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>
class DoNotTrackInterceptorInterface : public WebEngineViewer::NetworkPluginUrlInterceptorInterface
{
    Q_OBJECT
public:
    explicit DoNotTrackInterceptorInterface(QObject *parent = nullptr);
    ~DoNotTrackInterceptorInterface() override;

    [[nodiscard]] bool interceptRequest(QWebEngineUrlRequestInfo &info) override;
};

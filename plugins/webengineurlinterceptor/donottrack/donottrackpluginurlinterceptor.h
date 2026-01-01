/*
    SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QVariant>
#include <WebEngineViewer/NetworkPluginUrlInterceptor>
namespace WebEngineViewer
{
class NetworkPluginUrlInterceptorInterface;
}
class DoNotTrackPluginUrlInterceptor : public WebEngineViewer::NetworkPluginUrlInterceptor
{
    Q_OBJECT
public:
    explicit DoNotTrackPluginUrlInterceptor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~DoNotTrackPluginUrlInterceptor() override;

    [[nodiscard]] WebEngineViewer::NetworkPluginUrlInterceptorInterface *createInterface(QWebEngineView *webEngine, QObject *parent) override;
};

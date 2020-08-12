/*
    SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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

/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QVariant>
#include <WebEngineViewer/NetworkPluginUrlInterceptor>
class QWebEngineView;
namespace WebEngineViewer
{
class NetworkPluginUrlInterceptorInterface;
}
class AdblockPluginUrlInterceptor : public WebEngineViewer::NetworkPluginUrlInterceptor
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~AdblockPluginUrlInterceptor() override;

    WebEngineViewer::NetworkPluginUrlInterceptorInterface *createInterface(QWebEngineView *webEngine, QObject *parent) override;

    void showConfigureDialog(QWidget *parent) override;
    bool hasConfigureDialog() const override;
};

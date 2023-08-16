/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>
#include <WebEngineViewer/WebHitTestResult>
class QWebEngineView;
class AdblockInterceptorInterface : public WebEngineViewer::NetworkPluginUrlInterceptorInterface
{
    Q_OBJECT
public:
    explicit AdblockInterceptorInterface(QObject *parent = nullptr);
    ~AdblockInterceptorInterface() override;

    bool interceptRequest(QWebEngineUrlRequestInfo &info) override;
    QList<QAction *> interceptorUrlActions(const WebEngineViewer::WebHitTestResult &result) const override;
    void createActions(KActionCollection *ac) override;
    QWebEngineView *webEngineView() const;

    void setWebEngineView(QWebEngineView *webEngineView);

private:
    mutable WebEngineViewer::WebHitTestResult mCurrentWebHitTest;
    QAction *mShowBlockableItems = nullptr;
    QAction *mBlockImage = nullptr;
    QWebEngineView *mWebEngineView = nullptr;
};

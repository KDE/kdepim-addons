/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>
#include <WebEngineViewer/WebHitTestResult>
class QWebEngineView;
namespace AdBlock
{
class AdblockManager;
struct AdBlockResult;
}
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
    void slotBlockImage();
    void slotShowBlockableElement();
    void slotSearchItemsDone(const QVector<AdBlock::AdBlockResult> &result);
    mutable WebEngineViewer::WebHitTestResult mCurrentWebHitTest;
    QAction *mShowBlockableItems = nullptr;
    QAction *mBlockImage = nullptr;
    AdBlock::AdblockManager *const mAdblockManager;
    QWebEngineView *mWebEngineView = nullptr;
};


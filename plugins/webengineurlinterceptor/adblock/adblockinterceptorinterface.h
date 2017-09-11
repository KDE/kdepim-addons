/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef ADBLOCKINTERCEPTORINTERFACE_H
#define ADBLOCKINTERCEPTORINTERFACE_H

#include <WebEngineViewer/NetworkPluginUrlInterceptorInterface>
#include <WebEngineViewer/WebHitTestResult>
class QWebEngineView;
namespace AdBlock {
class AdblockManager;
class AdBlockResult;
}
class AdblockInterceptorInterface : public WebEngineViewer::NetworkPluginUrlInterceptorInterface
{
    Q_OBJECT
public:
    explicit AdblockInterceptorInterface(QObject *parent = nullptr);
    ~AdblockInterceptorInterface();

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
    AdBlock::AdblockManager *mAdblockManager = nullptr;
    QWebEngineView *mWebEngineView = nullptr;
};

#endif // ADBLOCKINTERCEPTORINTERFACE_H

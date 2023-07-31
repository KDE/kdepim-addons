/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockinterceptorinterface.h"
#include <QAction>
#include <QPointer>
#include <QWebEngineView>

AdblockInterceptorInterface::AdblockInterceptorInterface(QObject *parent)
    : WebEngineViewer::NetworkPluginUrlInterceptorInterface(parent)
{
}

AdblockInterceptorInterface::~AdblockInterceptorInterface() = default;

bool AdblockInterceptorInterface::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    return false;
    /*
        if (!mAdblockManager->isEnabled()) {
            return false;
        }
        return mAdblockManager->interceptRequest(info);
    */
}

QList<QAction *> AdblockInterceptorInterface::interceptorUrlActions(const WebEngineViewer::WebHitTestResult &result) const
{
    QList<QAction *> lstAction;
    /*
        if (mAdblockManager->isEnabled()) {
            lstAction.append(mShowBlockableItems);
            if (!result.imageUrl().isEmpty()) {
                lstAction.append(mBlockImage);
            }
            mCurrentWebHitTest = result;
        }
        */
    return lstAction;
}

void AdblockInterceptorInterface::createActions(KActionCollection *ac)
{
    /*
        if (ac) {
            mShowBlockableItems = new QAction(i18n("Open Blockable Items..."), this);
            ac->addAction(QStringLiteral("adblock_blockable_items"), mShowBlockableItems);
            connect(mShowBlockableItems, &QAction::triggered, this, &AdblockInterceptorInterface::slotShowBlockableElement);

            mBlockImage = new QAction(i18n("Block Image"), this);
            ac->addAction(QStringLiteral("adblock_image"), mBlockImage);
            ac->setShortcutsConfigurable(mBlockImage, false);
            connect(mBlockImage, &QAction::triggered, this, &AdblockInterceptorInterface::slotBlockImage);
        }
    */
}

QWebEngineView *AdblockInterceptorInterface::webEngineView() const
{
    return mWebEngineView;
}

void AdblockInterceptorInterface::setWebEngineView(QWebEngineView *webEngineView)
{
    mWebEngineView = webEngineView;
}

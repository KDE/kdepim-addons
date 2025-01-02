/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockinterceptorinterface.h"
#include "adblockinterceptor_debug.h"
#include "adblockmanager.h"
#include "globalsettings_webengineurlinterceptoradblock.h"
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
    if (!AdBlockSettings::self()->adBlockEnabled()) {
        qDebug(ADBLOCKINTERCEPTOR_LOG) << "Disable at the moment";
        return false;
    }
    qDebug(ADBLOCKINTERCEPTOR_LOG) << "Enabled at the moment";
    return AdblockManager::self()->interceptRequest(info);
}

QList<QAction *> AdblockInterceptorInterface::interceptorUrlActions(const WebEngineViewer::WebHitTestResult &result) const
{
    // TODO
    Q_UNUSED(result);
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
    // TODO
    Q_UNUSED(ac);
    /*
        if (ac) {
            mShowBlockableItems = new QAction(i18nc("@action", "Open Blockable Items…"), this);
            ac->addAction(QStringLiteral("adblock_blockable_items"), mShowBlockableItems);
            connect(mShowBlockableItems, &QAction::triggered, this, &AdblockInterceptorInterface::slotShowBlockableElement);

            mBlockImage = new QAction(i18nc("@action", "Block Image"), this);
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

#include "moc_adblockinterceptorinterface.cpp"

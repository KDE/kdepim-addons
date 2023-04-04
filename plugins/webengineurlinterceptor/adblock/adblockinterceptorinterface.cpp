/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockinterceptorinterface.h"
#include "../lib/adblockblockableitemsjob.h"
#include "../lib/widgets/adblockblockableitemsdialog.h"
#include "lib/adblockmanager.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
#include <QPointer>
#include <QWebEngineView>

AdblockInterceptorInterface::AdblockInterceptorInterface(QObject *parent)
    : WebEngineViewer::NetworkPluginUrlInterceptorInterface(parent)
    , mAdblockManager(new AdBlock::AdblockManager(this))
{
}

AdblockInterceptorInterface::~AdblockInterceptorInterface() = default;

bool AdblockInterceptorInterface::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if (!mAdblockManager->isEnabled()) {
        return false;
    }
    return mAdblockManager->interceptRequest(info);
}

QList<QAction *> AdblockInterceptorInterface::interceptorUrlActions(const WebEngineViewer::WebHitTestResult &result) const
{
    QList<QAction *> lstAction;
    if (mAdblockManager->isEnabled()) {
        lstAction.append(mShowBlockableItems);
        if (!result.imageUrl().isEmpty()) {
            lstAction.append(mBlockImage);
        }
        mCurrentWebHitTest = result;
    }
    return lstAction;
}

void AdblockInterceptorInterface::createActions(KActionCollection *ac)
{
    if (ac) {
        mShowBlockableItems = new QAction(i18n("Open Blockable Items..."), this);
        ac->addAction(QStringLiteral("adblock_blockable_items"), mShowBlockableItems);
        connect(mShowBlockableItems, &QAction::triggered, this, &AdblockInterceptorInterface::slotShowBlockableElement);

        mBlockImage = new QAction(i18n("Block Image"), this);
        ac->addAction(QStringLiteral("adblock_image"), mBlockImage);
        ac->setShortcutsConfigurable(mBlockImage, false);
        connect(mBlockImage, &QAction::triggered, this, &AdblockInterceptorInterface::slotBlockImage);
    }
}

QWebEngineView *AdblockInterceptorInterface::webEngineView() const
{
    return mWebEngineView;
}

void AdblockInterceptorInterface::setWebEngineView(QWebEngineView *webEngineView)
{
    mWebEngineView = webEngineView;
}

void AdblockInterceptorInterface::slotBlockImage()
{
    if (mCurrentWebHitTest.imageUrl().isValid()) {
        // qDebug() << " mCurrentWebHitTest.imageUrl()"<<mCurrentWebHitTest.imageUrl();
        // TODO block it.
    }
    // TODO
}

void AdblockInterceptorInterface::slotSearchItemsDone(const QList<AdBlock::AdBlockResult> &result)
{
    // TODO update
    QPointer<AdBlock::AdBlockBlockableItemsDialog> dlg = new AdBlock::AdBlockBlockableItemsDialog(mWebEngineView);
    dlg->setAdblockResult(result);
    dlg->exec();
    delete dlg;
}

void AdblockInterceptorInterface::slotShowBlockableElement()
{
    if (mWebEngineView) {
        auto job = new AdBlock::AdBlockBlockableItemsJob(this);
        job->setWebEngineView(mWebEngineView);
        connect(job, &AdBlock::AdBlockBlockableItemsJob::searchItemsDone, this, &AdblockInterceptorInterface::slotSearchItemsDone);
        job->start();
    }
}

/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "adblockinterceptorinterface.h"
#include "../lib/widgets/adblockblockableitemsdialog.h"
#include "../lib/adblockblockableitemsjob.h"
#include <QtWebEngineCore/qwebengineurlrequestinfo.h>
#include "lib/adblockmanager.h"
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QPointer>
#include <QWebEngineView>
#include <WebEngineViewer/WebHitTestResult>

AdblockInterceptorInterface::AdblockInterceptorInterface(QObject *parent)
    : WebEngineViewer::NetworkPluginUrlInterceptorInterface(parent),
      mShowBlockableItems(Q_NULLPTR),
      mWebEngineView(Q_NULLPTR)
{
    mAdblockManager = new AdBlock::AdblockManager(this);
}

AdblockInterceptorInterface::~AdblockInterceptorInterface()
{

}

bool AdblockInterceptorInterface::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if (!mAdblockManager->isEnabled()) {
        return false;
    }
    if (mAdblockManager->interceptRequest(info)) {
        return true;
    }
    return false;
}

QList<QAction *> AdblockInterceptorInterface::interceptorUrlActions(const WebEngineViewer::WebHitTestResult &result) const
{
    QList<QAction *> lstAction;
    qDebug() << " mAdblockManager->isEnabled()" << mAdblockManager->isEnabled();
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
        //TODO block it.
    }
    //TODO
}

void AdblockInterceptorInterface::slotSearchItemsDone(const QVector<AdBlock::AdBlockResult> &result)
{
    QPointer<AdBlock::AdBlockBlockableItemsDialog> dlg = new AdBlock::AdBlockBlockableItemsDialog(mWebEngineView);
    dlg->setAdblockResult(result);
    dlg->exec();
    delete dlg;
}

void AdblockInterceptorInterface::slotShowBlockableElement()
{
    if (mWebEngineView) {
        AdBlock::AdBlockBlockableItemsJob *job = new AdBlock::AdBlockBlockableItemsJob(this);
        job->setWebEngineView(mWebEngineView);
        connect(job, &AdBlock::AdBlockBlockableItemsJob::searchItemsDone, this, &AdblockInterceptorInterface::slotSearchItemsDone);
        job->start();
    }
}

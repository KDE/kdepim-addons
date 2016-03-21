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
#include <QtWebEngineCore/qwebengineurlrequestinfo.h>
#include "lib/adblockmanager.h"

AdblockInterceptorInterface::AdblockInterceptorInterface(QObject *parent)
    : MessageViewer::NetworkPluginUrlInterceptorInterface(parent),
      mWebEngineView(Q_NULLPTR)
{
    mAdblockManager = new AdBlock::AdblockManager(this);
}

AdblockInterceptorInterface::~AdblockInterceptorInterface()
{

}

void AdblockInterceptorInterface::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if (!mAdblockManager->isEnabled()) {
        return;
    }
    if (mAdblockManager->interceptRequest(info)) {
        info.block(true);
    }
}

QList<QAction *> AdblockInterceptorInterface::actions() const
{
    return mActionsList;
}

void AdblockInterceptorInterface::createActions(KActionCollection *ac)
{
    if (ac) {

    }
    //TODO
}

QWebEngineView *AdblockInterceptorInterface::webEngineView() const
{
    return mWebEngineView;
}

void AdblockInterceptorInterface::setWebEngineView(QWebEngineView *webEngineView)
{
    mWebEngineView = webEngineView;
}

void AdblockInterceptorInterface::slotShowBlockableElement()
{
    //TODO
}

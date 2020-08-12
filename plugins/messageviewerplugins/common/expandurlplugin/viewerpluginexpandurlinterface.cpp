/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexpandurlinterface.h"
#include "expandurlplugin_debug.h"
#include <MessageViewer/ScamExpandUrlJob>
#include <MessageViewer/ScamCheckShortUrlManager>
#include <MessageViewer/ScamCheckShortUrl>

#include <QAction>

#include <PimCommon/BroadcastStatus>
#include <KActionCollection>
#include <KLocalizedString>

using namespace MessageViewer;

ViewerPluginExpandurlInterface::ViewerPluginExpandurlInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginExpandurlInterface::~ViewerPluginExpandurlInterface()
{
}

QList<QAction *> ViewerPluginExpandurlInterface::actions() const
{
    return mAction;
}

void ViewerPluginExpandurlInterface::execute()
{
    if (mCurrentUrl.isValid()) {
        if (MessageViewer::ScamCheckShortUrlManager::self()->scamCheckShortUrl()->isShortUrl(mCurrentUrl)) {
            MessageViewer::ScamExpandUrlJob *job = new MessageViewer::ScamExpandUrlJob(this);
            job->expandedUrl(mCurrentUrl);
        } else {
            PimCommon::BroadcastStatus::instance()->setStatusMsg(i18n("Current URL is not a shortened URL."));
        }
    } else {
        qCWarning(EXPANDURLPLUGIN_LOG) << "Url is not valid";
    }
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginExpandurlInterface::featureTypes() const
{
    return NeedUrl;
}

void ViewerPluginExpandurlInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        QAction *act = new QAction(i18n("Expand URL"), this);
        ac->addAction(QStringLiteral("expand_short_url"), act);
        ac->setShortcutsConfigurable(act, false);
        connect(act, &QAction::triggered, this, &ViewerPluginExpandurlInterface::slotActivatePlugin);
        mAction.append(act);
    }
}

void ViewerPluginExpandurlInterface::setUrl(const QUrl &url)
{
    mCurrentUrl = url;
}

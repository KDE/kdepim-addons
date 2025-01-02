/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexpandurlinterface.h"
#include "expandurlplugin_debug.h"
#include <MessageViewer/ScamCheckShortUrl>
#include <MessageViewer/ScamCheckShortUrlManager>
#include <MessageViewer/ScamExpandUrlJob>

#include <QAction>

#include <KActionCollection>
#include <KLocalizedString>
#include <PimCommon/BroadcastStatus>

using namespace MessageViewer;

ViewerPluginExpandurlInterface::ViewerPluginExpandurlInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginExpandurlInterface::~ViewerPluginExpandurlInterface() = default;

QList<QAction *> ViewerPluginExpandurlInterface::actions() const
{
    return mAction;
}

void ViewerPluginExpandurlInterface::execute()
{
    if (mCurrentUrl.isValid()) {
        if (MessageViewer::ScamCheckShortUrlManager::self()->scamCheckShortUrl()->isShortUrl(mCurrentUrl)) {
            auto job = new MessageViewer::ScamExpandUrlJob(this);
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
        auto act = new QAction(i18nc("@action", "Expand URL"), this);
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

#include "moc_viewerpluginexpandurlinterface.cpp"

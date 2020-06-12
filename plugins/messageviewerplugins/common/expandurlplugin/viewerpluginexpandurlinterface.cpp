/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

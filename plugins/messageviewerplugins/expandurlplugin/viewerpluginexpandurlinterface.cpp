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

#include "viewerpluginexpandurlinterface.h"
#include <MessageViewer/ScamExpandUrlJob>
#include <MessageViewer/ScamCheckShortUrlManager>
#include <MessageViewer/ScamCheckShortUrl>

#include <QHBoxLayout>
#include <QIcon>
#include <QAction>

#include <KActionCollection>
#include <KLocalizedString>

using namespace MessageViewer;

ViewerPluginExpandurlInterface::ViewerPluginExpandurlInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent),
      mAction(Q_NULLPTR)
{
    createAction(ac);
}

ViewerPluginExpandurlInterface::~ViewerPluginExpandurlInterface()
{

}

QAction *ViewerPluginExpandurlInterface::action() const
{
    return mAction;
}

void ViewerPluginExpandurlInterface::showWidget()
{
    if (mCurrentUrl.isValid()) {
        if (MessageViewer::ScamCheckShortUrlManager::self()->scamCheckShortUrl()->isShortUrl(mCurrentUrl)) {
            MessageViewer::ScamExpandUrlJob *job = new MessageViewer::ScamExpandUrlJob(this);
            job->expandedUrl(mCurrentUrl);
        } else {
            //TODO message in statusbar.
        }
    }
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginExpandurlInterface::featureTypes() const
{
    return NeedUrl;
}

void ViewerPluginExpandurlInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        mAction = new QAction(i18n("Expand Url"), this);
        ac->addAction(QStringLiteral("expand_short_url"), mAction);
        ac->setShortcutsConfigurable(mAction, false);
        connect(mAction, &QAction::triggered, this, &ViewerPluginExpandurlInterface::slotActivatePlugin);
    }
}

void ViewerPluginExpandurlInterface::setUrl(const QUrl &url)
{
    mCurrentUrl = url;
}

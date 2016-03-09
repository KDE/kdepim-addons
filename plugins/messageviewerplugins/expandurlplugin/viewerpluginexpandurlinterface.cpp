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
    //Nothing
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginExpandurlInterface::featureTypes() const
{
    return NeedUrl;
}

void ViewerPluginExpandurlInterface::createAction(KActionCollection *ac)
{
    if (ac) {
#if 0
        mAction = new QAction(i18n("Translate..."), this);
        ac->setDefaultShortcut(mAction, QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_T));
        mAction->setIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-locale")));
        ac->addAction(QStringLiteral("translate_text"), mAction);
        connect(mAction, &QAction::triggered, this, &ViewerPluginExpandurlInterface::slotActivatePlugin);
#endif
    }
}

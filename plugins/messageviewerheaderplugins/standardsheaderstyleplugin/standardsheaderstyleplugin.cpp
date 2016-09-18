/*
   Copyright (C) 2015-2016 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "standardsheaderstyleplugin.h"
#include "standardsheaderstyleinterface.h"
#include "standardheaderstrategy.h"
#include "messageviewer/plainheaderstyle.h"
#include <kpluginfactory.h>
using namespace MessageViewer;

K_PLUGIN_FACTORY_WITH_JSON(MessageViewerStandardsHeaderStylePluginFactory, "messageviewer_standardsheaderstyleplugin.json", registerPlugin<StandardsHeaderStylePlugin>();)

StandardsHeaderStylePlugin::StandardsHeaderStylePlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::HeaderStylePlugin(parent),
      mHeaderStyle(new PlainHeaderStyle),
      mHeaderStrategy(new StandardHeaderStrategy)
{
}

StandardsHeaderStylePlugin::~StandardsHeaderStylePlugin()
{
    delete mHeaderStyle;
    delete mHeaderStrategy;
}

HeaderStyle *StandardsHeaderStylePlugin::headerStyle() const
{
    return mHeaderStyle;
}

HeaderStrategy *StandardsHeaderStylePlugin::headerStrategy() const
{
    return mHeaderStrategy;
}

HeaderStyleInterface *StandardsHeaderStylePlugin::createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent)
{
    MessageViewer::HeaderStyleInterface *view = new MessageViewer::StandardsHeaderStyleInterface(this, parent);
    if (ac) {
        view->createAction(menu, actionGroup, ac);
    }
    return view;
}

QString StandardsHeaderStylePlugin::name() const
{
    return QStringLiteral("standards-header");
}

#include "standardsheaderstyleplugin.moc"

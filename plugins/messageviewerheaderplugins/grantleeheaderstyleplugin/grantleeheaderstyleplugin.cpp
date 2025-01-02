/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grantleeheaderstyleplugin.h"
#include "grantleeheaderstrategy.h"
#include "grantleeheaderstyleinterface.h"
#include <MessageViewer/GrantleeHeaderStyle>

#include <KPluginFactory>
using namespace MessageViewer;

K_PLUGIN_CLASS_WITH_JSON(GrantleeHeaderStylePlugin, "messageviewer_grantleeheaderstyleplugin.json")

GrantleeHeaderStylePlugin::GrantleeHeaderStylePlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::HeaderStylePlugin(parent)
    , mHeaderStyle(new GrantleeHeaderStyle)
    , mHeaderStrategy(new GrantleeHeaderStrategy)
{
}

GrantleeHeaderStylePlugin::~GrantleeHeaderStylePlugin()
{
    delete mHeaderStyle;
    delete mHeaderStrategy;
}

HeaderStyle *GrantleeHeaderStylePlugin::headerStyle() const
{
    return mHeaderStyle;
}

HeaderStrategy *GrantleeHeaderStylePlugin::headerStrategy() const
{
    return mHeaderStrategy;
}

HeaderStyleInterface *GrantleeHeaderStylePlugin::createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent)
{
    MessageViewer::HeaderStyleInterface *view = new MessageViewer::GrantleeHeaderStyleInterface(this, parent);
    if (ac) {
        view->createAction(menu, actionGroup, ac);
    }
    return view;
}

QString GrantleeHeaderStylePlugin::name() const
{
    return QStringLiteral("grantlee");
}

#include "grantleeheaderstyleplugin.moc"

#include "moc_grantleeheaderstyleplugin.cpp"

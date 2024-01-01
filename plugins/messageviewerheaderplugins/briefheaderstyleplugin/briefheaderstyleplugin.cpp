/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "briefheaderstyleplugin.h"
#include "briefheaderstrategy.h"
#include "briefheaderstyle.h"
#include "briefheaderstyleinterface.h"
#include <KPluginFactory>

using namespace MessageViewer;

K_PLUGIN_CLASS_WITH_JSON(BriefHeaderStylePlugin, "messageviewer_briefheaderstyleplugin.json")

BriefHeaderStylePlugin::BriefHeaderStylePlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::HeaderStylePlugin(parent)
    , mHeaderStyle(new BriefHeaderStyle)
    , mHeaderStrategy(new BriefHeaderStrategy)
{
}

BriefHeaderStylePlugin::~BriefHeaderStylePlugin()
{
    delete mHeaderStyle;
    delete mHeaderStrategy;
}

HeaderStyle *BriefHeaderStylePlugin::headerStyle() const
{
    return mHeaderStyle;
}

HeaderStrategy *BriefHeaderStylePlugin::headerStrategy() const
{
    return mHeaderStrategy;
}

MessageViewer::HeaderStyleInterface *BriefHeaderStylePlugin::createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent)
{
    auto view = new MessageViewer::BriefHeaderStyleInterface(this, parent);
    if (ac) {
        view->createAction(menu, actionGroup, ac);
    }
    return view;
}

QString BriefHeaderStylePlugin::name() const
{
    return QStringLiteral("brief");
}

#include "briefheaderstyleplugin.moc"

#include "moc_briefheaderstyleplugin.cpp"

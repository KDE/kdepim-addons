/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "enterpriseheaderstyleplugin.h"
#include "enterpriseheaderstyle.h"
#include "enterpriseheaderstyleinterface.h"

#include <KPluginFactory>
#include <MessageViewer/RichHeaderStrategy>

using namespace MessageViewer;

K_PLUGIN_CLASS_WITH_JSON(EnterpriseHeaderStylePlugin, "messageviewer_enterpriseheaderstyleplugin.json")

EnterpriseHeaderStylePlugin::EnterpriseHeaderStylePlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::HeaderStylePlugin(parent)
    , mHeaderStyle(new EnterpriseHeaderStyle)
    , mHeaderStrategy(new RichHeaderStrategy)
{
}

EnterpriseHeaderStylePlugin::~EnterpriseHeaderStylePlugin()
{
    delete mHeaderStyle;
    delete mHeaderStrategy;
}

HeaderStyle *EnterpriseHeaderStylePlugin::headerStyle() const
{
    return mHeaderStyle;
}

HeaderStrategy *EnterpriseHeaderStylePlugin::headerStrategy() const
{
    return mHeaderStrategy;
}

HeaderStyleInterface *EnterpriseHeaderStylePlugin::createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent)
{
    MessageViewer::HeaderStyleInterface *view = new MessageViewer::EnterpriseHeaderStyleInterface(this, parent);
    if (ac) {
        view->createAction(menu, actionGroup, ac);
    }
    return view;
}

QString EnterpriseHeaderStylePlugin::name() const
{
    return QStringLiteral("enterprise");
}

bool EnterpriseHeaderStylePlugin::hasMargin() const
{
    return false;
}

QString EnterpriseHeaderStylePlugin::alignment() const
{
    return QStringLiteral("right");
}

int EnterpriseHeaderStylePlugin::elidedTextSize() const
{
    return 180;
}

#include "enterpriseheaderstyleplugin.moc"

#include "moc_enterpriseheaderstyleplugin.cpp"

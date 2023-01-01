/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardsheaderstyleplugin.h"
#include "standardheaderstrategy.h"
#include "standardsheaderstyleinterface.h"
#include <KPluginFactory>
#include <MessageViewer/PlainHeaderStyle>

using namespace MessageViewer;

K_PLUGIN_CLASS_WITH_JSON(StandardsHeaderStylePlugin, "messageviewer_standardsheaderstyleplugin.json")

StandardsHeaderStylePlugin::StandardsHeaderStylePlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::HeaderStylePlugin(parent)
    , mHeaderStyle(new PlainHeaderStyle)
    , mHeaderStrategy(new StandardHeaderStrategy)
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

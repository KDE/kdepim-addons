/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "longheaderstyleplugin.h"
#include "longheaderstyleinterface.h"
#include <MessageViewer/PlainHeaderStyle>

#include <KPluginFactory>
#include <MessageViewer/RichHeaderStrategy>

using namespace MessageViewer;

K_PLUGIN_CLASS_WITH_JSON(LongHeaderStylePlugin, "messageviewer_longheaderstyleplugin.json")

LongHeaderStylePlugin::LongHeaderStylePlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::HeaderStylePlugin(parent)
    , mHeaderStyle(new PlainHeaderStyle)
    , mHeaderStrategy(new RichHeaderStrategy)
{
}

LongHeaderStylePlugin::~LongHeaderStylePlugin()
{
    delete mHeaderStyle;
    delete mHeaderStrategy;
}

HeaderStyle *LongHeaderStylePlugin::headerStyle() const
{
    return mHeaderStyle;
}

HeaderStrategy *LongHeaderStylePlugin::headerStrategy() const
{
    return mHeaderStrategy;
}

HeaderStyleInterface *LongHeaderStylePlugin::createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent)
{
    MessageViewer::HeaderStyleInterface *view = new MessageViewer::LongHeaderStyleInterface(this, parent);
    if (ac) {
        view->createAction(menu, actionGroup, ac);
    }
    return view;
}

QString LongHeaderStylePlugin::name() const
{
    return QStringLiteral("long-header");
}

#include "longheaderstyleplugin.moc"

#include "moc_longheaderstyleplugin.cpp"

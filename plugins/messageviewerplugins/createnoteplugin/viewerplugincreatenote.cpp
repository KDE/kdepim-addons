/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreatenote.h"
#include "viewerplugincreatenoteinterface.h"
#include <KActionCollection>
#include <KPluginFactory>

using namespace MessageViewer;
K_PLUGIN_CLASS_WITH_JSON(ViewerPluginCreatenote, "messageviewer_createnoteplugin.json")

ViewerPluginCreatenote::ViewerPluginCreatenote(QObject *parent, const QList<QVariant> &)
    : MessageViewer::ViewerPlugin(parent)
{
}

ViewerPluginInterface *ViewerPluginCreatenote::createView(QWidget *parent, KActionCollection *ac)
{
    MessageViewer::ViewerPluginInterface *view = new MessageViewer::ViewerPluginCreatenoteInterface(ac, parent);
    return view;
}

QString ViewerPluginCreatenote::viewerPluginName() const
{
    return QStringLiteral("create-task");
}

#include "viewerplugincreatenote.moc"

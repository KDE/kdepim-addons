/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreatetodo.h"
#include "viewerplugincreatetodointerface.h"
#include <KActionCollection>
#include <KPluginFactory>

using namespace MessageViewer;
K_PLUGIN_CLASS_WITH_JSON(ViewerPluginCreatetodo, "messageviewer_createtodoplugin.json")

ViewerPluginCreatetodo::ViewerPluginCreatetodo(QObject *parent, const QList<QVariant> &)
    : MessageViewer::ViewerPlugin(parent)
{
}

ViewerPluginInterface *ViewerPluginCreatetodo::createView(QWidget *parent, KActionCollection *ac)
{
    MessageViewer::ViewerPluginInterface *view = new MessageViewer::ViewerPluginCreateTodoInterface(ac, parent);
    return view;
}

QString ViewerPluginCreatetodo::viewerPluginName() const
{
    return QStringLiteral("create-todo");
}

#include "viewerplugincreatetodo.moc"

#include "moc_viewerplugincreatetodo.cpp"

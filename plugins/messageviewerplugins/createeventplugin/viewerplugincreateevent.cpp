/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreateevent.h"
#include "viewerplugincreateeventinterface.h"
#include <KActionCollection>
#include <KPluginFactory>

using namespace MessageViewer;
K_PLUGIN_CLASS_WITH_JSON(ViewerPluginCreateevent, "messageviewer_createeventplugin.json")

ViewerPluginCreateevent::ViewerPluginCreateevent(QObject *parent, const QList<QVariant> &)
    : MessageViewer::ViewerPlugin(parent)
{
}

ViewerPluginInterface *ViewerPluginCreateevent::createView(QWidget *parent, KActionCollection *ac)
{
    MessageViewer::ViewerPluginInterface *view = new MessageViewer::ViewerPluginCreateEventInterface(ac, parent);
    return view;
}

QString ViewerPluginCreateevent::viewerPluginName() const
{
    return QStringLiteral("create-task");
}

#include "viewerplugincreateevent.moc"

#include "moc_viewerplugincreateevent.cpp"

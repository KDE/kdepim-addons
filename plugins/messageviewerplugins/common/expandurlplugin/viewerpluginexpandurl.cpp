/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexpandurl.h"
#include "viewerpluginexpandurlinterface.h"
#include <KActionCollection>
#include <KPluginFactory>

using namespace MessageViewer;
K_PLUGIN_CLASS_WITH_JSON(ViewerPluginExpandurl, "messageviewer_expandurlplugin.json")

ViewerPluginExpandurl::ViewerPluginExpandurl(QObject *parent, const QList<QVariant> &)
    : MessageViewer::ViewerPlugin(parent)
{
}

ViewerPluginInterface *ViewerPluginExpandurl::createView(QWidget *parent, KActionCollection *ac)
{
    MessageViewer::ViewerPluginInterface *view = new MessageViewer::ViewerPluginExpandurlInterface(ac, parent);
    return view;
}

QString ViewerPluginExpandurl::viewerPluginName() const
{
    return QStringLiteral("expandurl");
}

#include "viewerpluginexpandurl.moc"

#include "moc_viewerpluginexpandurl.cpp"
